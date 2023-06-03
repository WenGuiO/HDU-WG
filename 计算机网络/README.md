# 计算机网络

> 1. 记录与分享，方便自身学习记录。
>
> 2. 实验软件采用 Cisco Packet Tracer。
>
> 3. 以上皆为项目工程文件，可直接使用或修改。

## :star:1. 模块简述

共12个项目模块：

- LAB-1：路由模块
- LAB-2：NAT模块
- LAB-3：VLAN模块
- LAN-4：通信模块

## :star:2. Socket编程

### :sparkles:2.1 TCP 通信

**TCPServer:**

```java
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.net.ServerSocket;
import java.net.Socket;

/**
 * @author wengui
 */
public class TCPServer {
    public static void main(String[] args) throws Exception{
        System.out.println("_____TCP SERVER START_____");
        //创建 服务器套接字
        ServerSocket serverSocket = new ServerSocket(8080);
        //设置 超时时间 10s
        serverSocket.setSoTimeout(1000);

        while (true){
            try {
                //接收 客户端 请求
                Socket socket = serverSocket.accept();
                //获取 字节输入流
                InputStream read = socket.getInputStream();
                //转换 缓冲字符输入流
                BufferedReader bufferedReader = new BufferedReader(
                    new InputStreamReader(read));
                String msg;
                //逐行读取
                while((msg = bufferedReader.readLine()) != null){
                    //打印 信息
                    System.out.println("<" + socket.getRemoteSocketAddress()+ 
                                       ">说: " + msg);
                }
            } catch (IOException e) {
                break;
            }
        }

        serverSocket.close();
        System.out.println("_____TCP SERVER QUIT_____");
    }
}
```

**TCPClient:**

```java
import java.io.IOException;
import java.io.OutputStream;
import java.io.PrintStream;
import java.net.Socket;
import java.util.Scanner;

/**
 * @author wengui
 */
public class TCPClient {
    public static void main(String[] args) throws Exception {
        Socket socket = null;
        try {
            System.out.println("_____TCP CLIENT START_____");
            //创建 Socket 通信端点
            socket = new Socket("127.0.0.1", 8080);
            //获取 字节输出流
            OutputStream os = socket.getOutputStream();
            //转换 打印流, 方便直接发送 文本
            PrintStream ps = new PrintStream(os);

            Scanner sc = new Scanner(System.in);
            String msg;
            while (true) {
                System.out.println("<" + socket.getLocalSocketAddress() 
                                   + ">请说: ");
                msg = sc.nextLine();

                if ("quit".equals(msg)) {
                    break;
                }

                //发送
                ps.println(msg);
                ps.flush();

//                //若使用 字节流
//                // 将字符串转换为字节数组
//                byte[] buffer = msg.getBytes();
//
//                // 发送数据到服务器
//                os.write(buffer);
//                os.flush();
            }
        } catch (IOException e) {
            System.out.println("TCP SERVER IS CLOSED");
        }

        if (socket != null) {
            socket.close();
        }
        System.out.println("_____TCP CLIENT QUIT_____");
    }
}
```



### :sparkles:2.2 UDP通信

**UDPServer:**

```java
import java.net.DatagramPacket;
import java.net.DatagramSocket;

/**
 * @author wengui
 */
public class UDPServer {
    public static void main(String[] args) throws Exception {
        System.out.println("_____UDP SERVER START_____");
        //创建 UDP 套接字, 固定接口
        DatagramSocket socket = new DatagramSocket(9090);

        //设置超时时间为10秒
        socket.setSoTimeout(10000);

        byte[] buffer = new byte[1024*64];
        DatagramPacket packet = new DatagramPacket(buffer, buffer.length);

        while(true){
            try {
                //接收消息, 超时则执行 catch 操作
                socket.receive(packet);
                //打印消息
                System.out.println("来自<" + packet.getSocketAddress() + ">的信息: "
                        + new String(buffer, 0, packet.getLength()));


            }catch (Exception ignored){
                break;
            }
        }

        socket.close();
        System.out.println("_____UDP SERVER QUIT_____");
    }
}
```

**UDPClient:**

```java
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;
import java.util.Scanner;

/**
 * @author wengui
 */
public class UDPClient {
    public static void main(String[] args) throws Exception {
        System.out.println("_____UDP CLIENT START_____");
        //创建 UDP 套接字, 使用随机端口
        DatagramSocket socket = new DatagramSocket();

        //用户提供数据
        Scanner sc = new Scanner(System.in);
        String msg;

        while(true){
            System.out.println("<" + socket.getLocalPort() + "> 请说: ");
            msg = sc.nextLine();

            //退出
            if("quit".equals(msg)){
                break;
            }

            //将 字符串 转换为 字节
            byte[] buffer = msg.getBytes();

            //封装数据包 => 数据, 目的主机, 服务端口
            DatagramPacket packet = new DatagramPacket(buffer, buffer.length,
                    InetAddress.getLocalHost(), 9090);

            //发送数据包
            socket.send(packet);
        }

        socket.close();
        System.out.println("_____UDP CLIENT QUIT_____");
    }
}
```


