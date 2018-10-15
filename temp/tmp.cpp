// 1111111
void Initsocket(){
    WORD imgrequest;
    WSADATA wsadata;
    imgrequest = MAKEWORD(1, 1);
    int err;
    err = WSAStartup(imgrequest, &wsadata);
    if (!err){
        printf("服务已经启动\n");
    }else{
        printf("服务未启动\n");
        return;
    }
    SOCKET sersocket = socket(AF_INET, SOCK_STREAM, 0);

    SOCKADDR_IN addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);      //ip地址
    addr.sin_port = htons(8899);                        //绑定端口
    bind(sersocket, (SOCKADDR*)&addr, sizeof(SOCKADDR));//绑定完成
    listen(sersocket, 10);                              //其中第二个参数代表能够接收的最多的连接数

    SOCKADDR_IN clientsocket;
    int len = sizeof(SOCKADDR);
    boolean isConnected = false;

    int i = 0;
    while (true){
        SOCKET serConn = accept(sersocket, (SOCKADDR*)&clientsocket, &len);
        printf("客户端连接\n");
        //我这里起了一个线程来处理协议
        HANDLE hThread1 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)WorkThread, (LPVOID)serConn, 0, 0);
        if (hThread1 != NULL)
        {
            CloseHandle(hThread1);
        }
        Sleep(1000);    
        closesocket(serConn);
    }
}

///////2222222222

/*获取key和协议*/
void requestInfo(SOCKET sockClient, char * request){
    char recev[1024] = "";
    recv(sockClient, recev, 2048, 0);
    //cout << recev << endl;
    string s = recev;
    int i = s.find("Sec-WebSocket-Key");
    s = s.substr(i + 19, 24);
    //以上是为了得到客户端请求信息的key，关于key的作用可以去了解握手协议
    //以下是服务器拼接协议返回给客户端
    getKey(request,s);
}
/*协议
这个过程就是拿到客户端的key然后经过sha加密，再拼接返回的协议发给客户端
*/
void getKey(char *request, string clientkey){
    strcat(request, "HTTP/1.1 101 Switching Protocols\r\n");
    strcat(request, "Connection: upgrade\r\n");
    strcat(request, "Sec-WebSocket-Accept: ");
    string server_key = clientkey;
    server_key += "258EAFA5-E914-47DA-95CA-C5AB0DC85B11";
    SHA1  sha;
    unsigned int message_digest[5];
    cout <<"server_key:"<< server_key << endl;
    sha.Reset();
    sha << server_key.c_str();
    sha.Result(message_digest);
    for (int i = 0; i < 5; i++) {
        message_digest[i] = htonl(message_digest[i]);
    }
    server_key = base64_encode(reinterpret_cast<const unsigned char*>(message_digest), 20);
    server_key += "\r\n";
    strcat(request, server_key.c_str());
    strcat(request, "Upgrade: websocket\r\n\r\n");
    cout << "shalserver_key:" << server_key << endl;
}




/////33333333
/*工作线程*/
void WorkThread(SOCKET sockClient){
    char request[1024] = "";  //请求信息
    char clieninfo[2048]= ""; //握手后响应信息
    int len = 0;              //返回的长度
    int point = 0;            //字节指针位置
    int tmppoint = 0;         //临时指针变量

    //握手协议
    requestInfo(sockClient, request);
    respondInfo(sockClient, request);
    //以上是握手协议
    //握手协议结束后，也就是服务返回给客户端后，客户端再一次返回
    //数据给服务器，下面就是解析客户端的返回数据
    //将数据全部读取出来
    len=recv(sockClient, clieninfo, 2048, 0);
    string ss = clieninfo;
    cout << "数据长度\n："<<len <<"乱码数据："<< ss << endl;

    if (len>0){
    /*这里b字节数组是客户端的请求信息，需要注意point这个指针的变化，具体需要去理解它的协议，协议中每段字节里面包含了什么信息需要把    它解析出来*/
        byte b[4096] = "";
        //转为字节来处理
        memcpy(b, clieninfo, 2048);
        cout << "字节数据：" << b << endl;
        for (int i = 0; i <= 33; i++){
            printf("%d\t", b[i]);
        }
        printf("\n");
        //取第一个字节
        int first = b[point] & 0xFF;
        printf("第一个：%d,%d,%d\n", point, b[point], first);
        byte opCode = (byte)(first & 0x0F);             //0000 1111 后四位为opCode 00001111
        if (opCode == 8){
            closesocket(sockClient);
        }
        //取第二个字节
        first = b[++point];
        //负载长度
        int payloadLength = first & 0x7F;
        printf("第二个：%d,[%d],%d\n", point, b[point], payloadLength);
        if (payloadLength == 126) {
            byte extended[2] = "";
            extended[0] = b[++point];
            extended[1] = b[++point];
            int shift = 0;
            payloadLength = 0;
            for (int i = 2- 1; i >= 0; i--) {
                payloadLength = payloadLength + ((extended[i] & 0xFF) << shift);
                shift += 8;
            }
        }else if (payloadLength == 127) {
            byte extended[8] = "";
            tmppoint = ++point;     //保存临时指针
            point = --point;
            for (int i = 0; i < 8;i++){
                extended[i] = b[tmppoint + i];
                point++;
            }
            int shift = 0;
            payloadLength = 0;
            for (int i = 8 - 1; i >= 0; i--) {
                payloadLength = payloadLength + ((extended[i] & 0xFF) << shift);
                shift += 8;
            }
        }

        //非126和127置回来
        if ((payloadLength != 126) || (payloadLength != 127)){
            point = 1;              
        }

        cout << "负载长度:" << payloadLength << endl;
        //第三个字节，掩码
        byte mask[4] = "";
        tmppoint = ++point;
        //因为自增了一次，这里需要减掉
        point = --point; 
        //取掩码值
        for (int i = 0; i < 4; i++){
            mask[i] = b[tmppoint + i];
            point++;
            printf("第三mask个：%d,[%d],%d\t\n", point, mask[i], payloadLength);
        }
        byte changeb[4096] = "";

        //内容的长度保留，循环里面已经被改变
        int length = payloadLength;
        int readThisFragment = 1;

        //通过掩码计算真实的数据
        while (payloadLength > 0){
            int maskbyte = b[++point];
            int index = (readThisFragment - 1) % 4;
            maskbyte = maskbyte ^ (mask[index] & 0xFF);
            changeb[readThisFragment-1] = (byte)maskbyte;
            printf("内容：%d,[%d],%d\n", point, maskbyte, readThisFragment);
            payloadLength--;
            readThisFragment++;
        }
        char a[4096] = "1231";
        byte test[1024] = "";
        memcpy(test, a, strlen(a));

        Sleep(5000);//这里是模拟处理其他事情
        //响应客户端
        //respondClient(sockClient, changeb, length, true);
        respondClient(sockClient, test, strlen(a), true);

        //打印客户端的数据
        char charb[4096] = "";
        memcpy(charb, changeb, length);
        //charb[length] = 0;
        for (int i = 0; i < length;i++){
            printf("%d\t", charb[i]);
        }
        printf("%d\n");
        string s = charb;
        cout << "客户端数据：" << s << endl;
        //closesocket(sockClient);
    }
}
/*发送协议*/
void respondInfo(SOCKET sockClient, char * request){
    send(sockClient, request, strlen(request), 0);
}








///////444444
/*给客户端发送数据也需要进行加密处理，就是保持通讯协议*/
void respondClient(SOCKET sockClient, byte charb[],int length, boolean finalFragment){
    byte buf[1024] = "";
    int first = 0x00;
    int tmp = 0;
    if (finalFragment) {
        first = first + 0x80;
        first = first + 0x1;
    }
    buf[0] = first;
    tmp = 1;
    cout <<"数组长度:"<< length << endl;
    unsigned int nuNum = (unsigned)length;
    if (length < 126) {
        buf[1] = length;
        tmp = 2;
    }else if (length < 65536) {
        buf[1] = 126;
        buf[2] = nuNum >> 8;
        buf[3] = length & 0xFF;
        tmp = 4;
    }else {
        //数据长度超过65536
        buf[1] = 127;
        buf[2] = 0;
        buf[3] = 0;
        buf[4] = 0;
        buf[5] = 0;
        buf[6] = nuNum >> 24;
        buf[7] = nuNum >> 16;
        buf[8] = nuNum >> 8;
        buf[9] = nuNum & 0xFF;
        tmp = 10;
    }
    for (int i = 0; i < length;i++){
        buf[tmp+i]= charb[i];
        printf("要发送的数据字节：%d\n", charb[i]);
    }
    char charbuf[1024] = "";
    memcpy(charbuf, buf, length + tmp);
    send(sockClient, charbuf, 1024, 0);
}





////55555555
(function(){
    var $ = function(id){return document.getElementById(id) || null;}
    var wsServer = 'ws://127.0.0.1:8080'; 
    var ws = new WebSocket(wsServer);
    var isConnect = false;
    ws.onopen = function (evt) { onOpen(evt) }; 
    ws.onclose = function (evt) { onClose(evt) }; 
    ws.onmessage = function (evt) { onMessage(evt) }; 
    ws.onerror = function (evt) { onError(evt) }; 
    function onOpen(evt) { 
        console.log("连接服务器成功");
        isConnect = true;
    } 
    function onClose(evt) { 
        //console.log("Disconnected"); 
    } 
    function onMessage(evt) {
        console.log('Retrieved data from server: ' + evt.data);
    }
    function onError(evt) { 
        //console.log('Error occured: ' + evt.data); 
    }
    function sendMsg() {
        if(isConnect){
            ws.send('hello');
        }
    }
})();