
package cs250.hw3;

import java.net.Socket;
import java.net.InetAddress;
import java.util.ArrayList;
import java.util.Random;
import java.io.*;

public class TCPClient {

    Socket clientSocket;
    DataInputStream dataInputStream;
    DataOutputStream dataOutputStream;
    String serverHostName;
    ArrayList<Integer> receivedData;
    ArrayList<Integer> receivedClientData;
    int serverPortNum;
    long senderSum;
    long receiverSum;
    int numMessagesSent;
    int numMessagesReceived;
    
    public TCPClient(String serverHostName, int serverPortNum) {
        this.serverHostName = serverHostName;
        this.serverPortNum  = serverPortNum;
        this.senderSum = 0;
        this.numMessagesSent = 0;
        receivedData = new ArrayList<>();
        receivedClientData = new ArrayList<>();
    }

    public void connect() throws IOException{
        try {
            clientSocket = new Socket(serverHostName, serverPortNum);
        } catch (IOException e) {
            throw e;
        }
    }

    public void receiveDataFromServer() throws IOException {

        try {
            dataInputStream = new DataInputStream(clientSocket.getInputStream());
            receivedData.add(dataInputStream.readInt());
            receivedData.add(dataInputStream.readInt());
            System.out.println("Received config");
        } catch (IOException e) {
            throw e;
        }
    }

    public void receiveClientDataFromServer() throws IOException {
        System.out.println("Starting to listen for messages from server...");
        try {
            dataInputStream = new DataInputStream(clientSocket.getInputStream());
            for (int i = 0; i < numMessagesSent; i++) {
                receivedClientData.add(dataInputStream.readInt());
                receiverSum += receivedClientData.get(i);
                numMessagesReceived++;
            }
            System.out.println("Finished listening to messages from server.");
        } catch (IOException e) {
            throw e;
        }
    }

    public void printDataFromServer() {
        System.out.println("number of messages = " + receivedData.get(0));
        System.out.println("seed = " + receivedData.get(1));
    }

    public void printClientDataFromServer() {
        System.out.println("Total messages received: " + numMessagesReceived);
        System.out.println("Sum of messages received: " + receiverSum);
    }

    public void sendDataToServer() throws IOException{
        Random randomNumGen = new Random(receivedData.get(1));
        int randomNum;
        System.out.println("Starting to send messages to server...");
        try {
            OutputStream outputStream = clientSocket.getOutputStream();
            dataOutputStream = new DataOutputStream(outputStream); 
            for (int i = 0; i < receivedData.get(0); i++) {
                randomNum = randomNumGen.nextInt();
                dataOutputStream.writeInt(randomNum);
                senderSum += randomNum;
                numMessagesSent++;
            }
            dataOutputStream.flush();
            System.out.println("Finished sending messages to server.");
            System.out.println("Total messages sent: " + numMessagesSent + 
                               "\nSum of messages sent: " + senderSum);
        } catch (IOException e) {
            throw e;
        }   
    }

    public void stop() {
        try {
            clientSocket.close();
            dataOutputStream.close();
            dataInputStream.close();
        } catch (IOException e) {
            System.out.println(e.getMessage());
        }
    }

    public static void main(String args[]) {

        try {
            if (args.length != 2) {
                throw new IOException("Length of args is " + args.length + ", should be 2.");
            } 
            String serverHostName = args[0];
            int serverPortNum = Integer.parseInt(args[1]);

            TCPClient client = new TCPClient(serverHostName, serverPortNum);
            client.connect();
            client.receiveDataFromServer();
            client.printDataFromServer();
            client.sendDataToServer();
            client.receiveClientDataFromServer();
            client.printClientDataFromServer();
            client.stop();
            
        } catch (IOException e) {
            System.out.println(e.getMessage());
        }
    }
}