# ChatSystem
## 使用说明
1.下载文件后，使用CMake分别创建工程，结果为两个sln工程--ChatServer.sln和ChatClient.sln；  
2.编译工程，编译完成后在两个工程目录下分别会有一个Debug文件夹；  
（创建工程和编译过程的操作可以参考 https://www.cnblogs.com/lidabo/p/8652429.html ）  
3.进入Debug文件夹，在ChatServer工程下有ChatServer.exe文件，在ChatClient工程下有ChatClient.exe文件;  
4.在ChatServer文件夹目录下打开1个cmd窗口--A，在ChatClient文件夹目录下打开2个cmd窗口--B和C；  
5.窗口A启动服务器，命令为ChatServer.exe 12345，12345是服务器端口号，可以自己定；  
6.窗口B启动一个客户端，命令为ChatClient.exe 127.0.0.1 12345，127.0.0.1是服务器IP地址，12345是服务器端口号，端口号应与服务器窗口一致；  
7.窗口C启动另一个客户端，命令与窗口B一致；  
8.两个客户端启动后，要先进行登录，代码中写死了两个用户，aa和bb，密码分别是123和789；  
9.登录成功后，程序会提示选择是否要发起聊天，用户可以输入yes或no，若输入yes，该客户端将先进入发送信息状态，若输入no，该客户端将先进入接收信息状态；  
（为保证聊天正常进行，请确保两个客户端一个输入yes，另一个输入no）  
10.输入yes的客户端将先向对方客户端发送信息；  
10.选择完成后，就可以进行聊天了  
