
package cs250.hw3;

import java.net.ServerSocket;
import java.net.Socket;
import java.net.InetAddress;
import java.net.UnknownHostException;
import java.util.Random;
import java.util.ArrayList;
import java.io.*;

public class TCPServer{

    ServerSocket serverSocket;
    Socket client01Socket;
    Socket client02Socket;
    DataInputStream dataInputStreamClient01;
    DataInputStream dataInputStreamClient02;
    DataOutputStream dataOutputStream;
    Random randomNumGen;
    int serverPortNumber = 0;
    int serverSeed = 0;
    int numClientMessages = 0;

    ArrayList<Integer> receivedDataClient01;
    ArrayList<Integer> receivedDataClient02;

    public TCPServer(int serverPortNumber, int serverSeed, int numClientMessages) {
        this.serverPortNumber = serverPortNumber;
        this.serverSeed = serverSeed;
        this.numClientMessages = numClientMessages;
        this.randomNumGen = new Random(serverSeed);
    }

    public void start() throws IOException{
        try {
            initServerSocket();
            printServerInfo();
            initClientSockets();
        } catch (IOException e) {
            throw e;
        }
    }

    public void stop() {
        try {
            serverSocket.close();
            client01Socket.close();
            client02Socket.close();
            dataOutputStream.close();
        } catch (IOException e) {
            System.out.println(e.getMessage());
        }
    }

    public void sendDataTask02() throws IOException{
        try {
            System.out.println("Sending config to clients...");

            int randomNum = randomNumGen.nextInt();
            System.out.println(client01Socket.getInetAddress().getHostName() + " " + randomNum);
            dataOutputStream = new DataOutputStream(client01Socket.getOutputStream());
            dataOutputStream.writeInt(numClientMessages);
            dataOutputStream.writeInt(randomNum);
            dataOutputStream.flush();

            randomNum = randomNumGen.nextInt();
            System.out.println(client02Socket.getInetAddress().getHostName() + " " + randomNum);
            dataOutputStream = new DataOutputStream(client02Socket.getOutputStream());
            dataOutputStream.writeInt(numClientMessages);
            dataOutputStream.writeInt(randomNum);
            dataOutputStream.flush();

            System.out.println("Finished sending config to clients.");
        } catch (IOException e) {
            throw e;
        }
    }

    private void receiveDataTask03() throws IOException{
        try {
            receiveDataFromClient();
            System.out.println(client01Socket.getInetAddress().getHostName() + 
                            "\n      Messages received: " + receivedDataClient01.size() + 
                            "\n      Sum received: " + calcArrayListSum(receivedDataClient01));
            System.out.println(client02Socket.getInetAddress().getHostName() + 
                            "\n      Messages received: " + receivedDataClient02.size() + 
                            "\n      Sum received: " + calcArrayListSum(receivedDataClient02));
        } catch (IOException e) {
            throw e;
        }
    }

    private void sendClientDataTask04() throws IOException{
        try {
            sendDatatoClient(client01Socket, receivedDataClient02);
            sendDatatoClient(client02Socket, receivedDataClient01);
        } catch (IOException e) {
            throw e;
        }
    }

    private void initServerSocket() throws IOException{
        try {
            serverSocket = new ServerSocket(serverPortNumber, 2, InetAddress.getLocalHost());
        } catch (IOException e) {
            throw new IOException("Address already in use (Bind Failed)");
        }
    }

    private void initClientSockets() throws IOException{
        try {
            System.out.println("waiting for client...");
            client01Socket = serverSocket.accept();
            client02Socket = serverSocket.accept();
            System.out.println("Clients Connected!");
        } catch (IOException e) {
            throw e;
        }
    }

    private void printServerInfo() {
        System.out.println("IP Address: " + serverSocket.getInetAddress());
        System.out.println("Port Number " + serverSocket.getLocalPort());
    }

    public void receiveDataFromClient() throws IOException {
        
        receivedDataClient01 = new ArrayList<>();
        receivedDataClient02 = new ArrayList<>();
        System.out.println("Starting to listen for client messages...");
        try {
            dataInputStreamClient01 = new DataInputStream(client01Socket.getInputStream());
            dataInputStreamClient02 = new DataInputStream(client02Socket.getInputStream());
            System.out.println("Finished listening for client messages.");

            for (int i = 0; i < numClientMessages; i++) {
                receivedDataClient01.add(dataInputStreamClient01.readInt());
            }
            for (int i = 0; i < numClientMessages; i++) {
                receivedDataClient02.add(dataInputStreamClient02.readInt());
            }
        } catch (IOException e) {
            throw e;
        }
    }

    private void sendDatatoClient(Socket clientSocket, ArrayList<Integer> dataToSend) throws IOException {
        try {
            dataOutputStream = new DataOutputStream(clientSocket.getOutputStream());
            for (int i = 0; i < dataToSend.size(); i++) {
                dataOutputStream.writeInt(dataToSend.get(i));
            }
            dataOutputStream.flush();
        } catch (IOException e) {
            throw e;
        }
    }

    public long calcArrayListSum(ArrayList<Integer> arr) {
        long sum = 0;
        for (int i = 0; i < arr.size(); i++) {
            sum += arr.get(i);
        }
        return sum;
    }

    public static void main(String args[]) {

        try {

            if (args.length != 3) {
                throw new IOException("Error: Length of args is " + args.length + ", should be 3");
            }
            int serverPortNumber = Integer.parseInt(args[0]);
            int serverSeed = Integer.parseInt(args[1]);
            int numClientMessages = Integer.parseInt(args[2]);

            if (serverPortNumber < 1024 || serverPortNumber > 65535) {
                throw new IOException("Server Port Number is not within range [1024, 65535]");
            }

            TCPServer server = new TCPServer(serverPortNumber, serverSeed, numClientMessages);
            server.start();
            server.sendDataTask02();
            server.receiveDataTask03();
            server.sendClientDataTask04();
            server.stop();
        } catch (IOException e) {
            System.out.println(e.getMessage());
        }
    }
}