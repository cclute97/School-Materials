
package cs250.hw1;

import java.util.ArrayList;
import java.util.LinkedList;
import java.util.Queue;
import java.util.Stack;

public class Operations {


    // Task Methods // 


    // checks and prints the types for all Strings in nums[] (nums[] being args[] in main) - Tested
    public static void printType(String nums[]) {

        for (int i = 0; i < nums.length; i++) {
            if (nums[i].substring(0, 2).equals("0b")) {
                System.out.println(nums[i] + "=Binary");
            }
            else if (nums[i].substring(0, 2).equals("0x")) {
                System.out.println(nums[i] + "=Hexadecimal");
            }
            else {
                System.out.println(nums[i] + "=Decimal");
            }
        }
    }

    // checks the given strings for correct format, and prints.  Returns boolean true if all correct, false otherwise - Tested
    public static boolean correctFormat(String nums[]) {

        boolean correctFormats = true;
        boolean currentCorrect = true;

        for (int i = 0; i < nums.length; i++) {
            if (nums[i].substring(0, 2).equals("0b")) {
                for (int j = 2; j < nums[i].length(); j++) {
                    if (nums[i].charAt(j) != '0' && nums[i].charAt(j) != '1') {
                        correctFormats = false;
                        System.out.println(nums[i] + "=false");
                        currentCorrect = false;
                        break;
                    }
                }
                if (currentCorrect) {
                    System.out.println(nums[i] + "=true");
                }
                else {
                    currentCorrect = true;
                }
                
            }
            else if (nums[i].substring(0, 2).equals("0x")) {

                String hexadecimalChars = "0123456789ABCDEFabcdef";

                for (int j = 2; j < nums[i].length(); j++) {
                    if (!(hexadecimalChars.contains(String.valueOf(nums[i].charAt(j))))) {
                        correctFormats = false;
                        System.out.println(nums[i] + "=false");
                        currentCorrect = false;
                        break;
                    }
                }
                if (currentCorrect) {
                    System.out.println(nums[i] + "=true");
                }
                else {
                    currentCorrect = true;
                }
            }
            else {
                
                String decimalChars = "0123456789";

                for (int j = 2; j < nums[i].length(); j++) {
                    if (!(decimalChars.contains(String.valueOf(nums[i].charAt(j))))) {
                        correctFormats = false;
                        System.out.println(nums[i] + "=false");
                        currentCorrect = false;
                        break;
                    }
                }
                if (currentCorrect) {
                    System.out.println(nums[i] + "=true");
                }
                else {
                    currentCorrect = true;
                }

            }
        }
        return correctFormats;
    }

    // Converts each number into binary, decimal, and hexadecimal, then prints - Not Tested
    public static void convertTypes(String nums[]) {
        
        for (int i = 0; i < nums.length; i++) {

            if (i == 0) {
                System.out.print("Start=" + nums[i] + ",");
            }
            else {
                System.out.print("\nStart=" + nums[i] + ",");
            }

            if (nums[i].substring(0, 2).equals("0b")) { // if already binary, print as is
                System.out.print("Binary=" + nums[i] + ",");
            }   
            else { // if not already binary, convert and print
                if (nums[i].substring(0, 2).equals("0x")) { // hexadecimal to binary - Tested
                    System.out.print("Binary=0b" + hexToBinaryWithReturn(nums[i]) + ",");
                }
                else { // decimal to binary - Tested
                    System.out.print("Binary=0b" + decimalToBinaryWithReturn(nums[i]) + ",");
                }
            }

            if (!(nums[i].substring(0, 2).equals("0b")) && !(nums[i].substring(0, 2).equals("0x"))) { // if already decimal, print as is
                System.out.print("Decimal=" + nums[i] + ",");
            }
            else { // if not already decimal, convert and print
                if (nums[i].substring(0, 2).equals("0b")) { // binary to decimal - Tested
                    System.out.print("Decimal=" + binaryToDecimalWithReturn(nums[i]) + ",");
                }
                else { // hexadecimal to decimal - Tested
                    System.out.print("Decimal=" + hexToDecimalWithReturn(nums[i]) + ",");
                }
            }

            if (nums[i].substring(0, 2).equals("0x")) { // if already hexadecimal, print as is
                System.out.print("Hexadecimal=" + nums[i]);
            }
            else { // if not already hexadecimal, convert and print
                if (nums[i].substring(0, 2).equals("0b")) { // binary to hexadecimal - Not Tested
                    System.out.print("Hexadecimal=0x" + decimalToHexWithReturn(binaryToDecimalWithReturn(nums[i])));
                }
                else { // decimal to hexadecimal - Tested
                    System.out.print("Hexadecimal=0x" + decimalToHexWithReturn(nums[i]));
                }
            }
        }
        System.out.println(); // Newline
    }

    // Converts each number to binary, then prints the ones complement of that binary string 
    public static void onesComplement(String nums[]) {

        String temp = ""; // used to store converted hex/dec -> binary vals

        for (int i = 0; i < nums.length; i++) {

            System.out.print(nums[i] + "=");

            if (nums[i].substring(0, 2).equals("0b")) { // if already binary
                System.out.print(nums[i].substring(2) + "=>");
                System.out.print(binaryOnesComplementWithReturn(nums[i].substring(2)));
            }
            else { // otherwise, convert to binary
                if (nums[i].substring(0, 2).equals("0x")) { // hexadecimal to binary
                    temp = hexToBinaryWithReturn(nums[i]);
                    System.out.print(temp + "=>");
                    System.out.print(binaryOnesComplementWithReturn(temp));
                }
                else { // decimal to binary
                    temp = decimalToBinaryWithReturn(nums[i]);
                    System.out.print(temp + "=>");
                    System.out.print(binaryOnesComplementWithReturn(temp));
                }
            }
            System.out.println(); // Newline
        }

    }

    // Converts each number to binary, then prints the two's complement of that binary string 
    public static void twosComplement(String nums[]) {

        String temp = ""; // used to store converted hex/dec -> binary vals

        for (int i = 0; i < nums.length; i++) {

            System.out.print(nums[i] + "=");

            if (nums[i].substring(0, 2).equals("0b")) { // if already binary
                System.out.print(nums[i].substring(2) + "=>");
                System.out.print(binaryTwoComplementWithReturn(nums[i].substring(2)));
            }
            else { // otherwise, convert to binary
                if (nums[i].substring(0, 2).equals("0x")) { // hexadecimal to binary
                    temp = hexToBinaryWithReturn(nums[i]);
                    System.out.print(temp + "=>");
                    System.out.print(binaryTwoComplementWithReturn(temp));
                }
                else { // decimal to binary
                    temp = decimalToBinaryWithReturn(nums[i]);
                    System.out.print(temp + "=>");
                    System.out.print(binaryTwoComplementWithReturn(temp));
                }
            }
            System.out.println(); // Newline
        }

    }

    // Prints the bitwise operations OR, AND, and XOR
    public static void bitwiseOperations(String nums[]) {

        StringBuilder sb = new StringBuilder("");
        String[] binaryStringsArray = new String[nums.length]; // converted nums to binary
        String[] binaryStringArrayLeadingZero = new String[nums.length]; // binary nums with leading zeros -- all same length
        Stack<String> stack = new Stack<>();
        int longestStringLength;

        for (int i = 0; i < nums.length; i++) { // convert strings contained within nums into binary strings and add to binaryStringArray
            if (nums[i].substring(0, 2).equals("0b")) { // if binary
                binaryStringsArray[i] = nums[i].substring(2);
            }
            else if (nums[i].substring(0, 2).equals("0x")) { // if hexadecimal
                binaryStringsArray[i] = hexToBinaryWithReturn(nums[i]);
            }
            else { // if decimal 
                binaryStringsArray[i] = decimalToBinaryWithReturn(nums[i]);
            }
        }

        longestStringLength = maxVal(binaryStringsArray[0].length(), binaryStringsArray[1].length(), binaryStringsArray[2].length());

        for (int i = 0; i < binaryStringsArray.length; i++) { // add leading zeros to shorter binary strings so that all three strings are the same length
            if (binaryStringsArray[i].length() < longestStringLength) {
                binaryStringArrayLeadingZero[i] = addLeadingZerosBinary(binaryStringsArray[i], (longestStringLength - binaryStringsArray[i].length()));
            }
            else {
                binaryStringArrayLeadingZero[i] = binaryStringsArray[i];
            }
        }

        // Bitwise OR // 

        for (int i = longestStringLength - 1; i >= 0; i--) {
            if (binaryStringArrayLeadingZero[0].charAt(i) == '1' || 
                binaryStringArrayLeadingZero[1].charAt(i) == '1' || 
                binaryStringArrayLeadingZero[2].charAt(i) == '1') {
                
                stack.push("1");

            }
            else {
                stack.push("0");
            }
        }

        int stackSize = stack.size();
        for (int i = 0; i < stackSize; i++) {
            sb.append(stack.pop());
        }

        System.out.println(binaryStringsArray[0] + "|" + binaryStringsArray[1] + "|" + binaryStringsArray[2] + "=" + sb.toString());

        // Bitwise AND //

        sb.delete(0, sb.length()); // clear out stringbuilder

        for (int i = longestStringLength - 1; i >= 0; i--) {
            if (binaryStringArrayLeadingZero[0].charAt(i) == '1' && 
                binaryStringArrayLeadingZero[1].charAt(i) == '1' && 
                binaryStringArrayLeadingZero[2].charAt(i) == '1') {
                
                stack.push("1");

            }
            else {
                stack.push("0");
            }
        }

        stackSize = stack.size();
        for (int i = 0; i < stackSize; i++) {
            sb.append(stack.pop());
        }

        System.out.println(binaryStringsArray[0] + "&" + binaryStringsArray[1] + "&" + binaryStringsArray[2] + "=" + sb.toString());

        // Bitwise XOR -- Exclusive OR -- one or all bits// 

        sb.delete(0, sb.length()); // clear out stringbuilder
        int[] bits = new int[3];

        for (int i = longestStringLength - 1; i >= 0; i--) {
            for (int j = 0; j < 3; j++) {
                if (binaryStringArrayLeadingZero[j].charAt(i) == '1') {
                    bits[j] = 1;
                }
                else {
                    bits[j] = 0;
                }
            }
            
            if (arraySum(bits) == 3 || arraySum(bits) == 1) {
                stack.push("1");
            }
            else {
                stack.push("0");
            }
            
        }

        stackSize = stack.size();
        for (int i = 0; i < stackSize; i++) {
            sb.append(stack.pop());
        }
        
        System.out.println(binaryStringsArray[0] + "^" + binaryStringsArray[1] + "^" + binaryStringsArray[2] + "=" + sb.toString());
    }

    // Prints the bitshift operations
    public static void bitShiftOperations(String nums[]) {

        String[] binaryStringsArray = new String[nums.length];

        for (int i = 0; i < nums.length; i++) { // convert strings contained within nums into binary strings and add to binaryStringArray
            if (nums[i].substring(0, 2).equals("0b")) { // if binary
                binaryStringsArray[i] = nums[i].substring(2);
            }
            else if (nums[i].substring(0, 2).equals("0x")) { // if hexadecimal
                binaryStringsArray[i] = hexToBinaryWithReturn(nums[i]);
            }
            else { // if decimal 
                binaryStringsArray[i] = decimalToBinaryWithReturn(nums[i]);
            }
        }

        for (int i = 0; i < binaryStringsArray.length; i++) {
            System.out.println(binaryStringsArray[i] + "<<2=" + bitShiftLeft(binaryStringsArray[i], 2) + "," + 
                               binaryStringsArray[i] + ">>2=" + bitShiftRight(binaryStringsArray[i], 2));
        }
    }


    // Helper Methods // 

    // return int product of base^power
    public static int powProduct(int base, int power) {
        if (power < 1) {
            return 1;
        }
        else {
            return base * powProduct(base, power - 1);
        }
    }


    // returns string of leftshifted bits
    public static String bitShiftLeft(String bitString, int shiftSize) {
        StringBuilder sb = new StringBuilder("");
        for (int i = 0; i < shiftSize; i++) {
            sb.append("0");
        }
        return bitString + sb.toString();
    }

    // returns String of rightshifted bits
    public static String bitShiftRight(String bitString, int shiftSize) {
        return bitString.substring(0, bitString.length() - shiftSize);
    }

    // returns sum of array
    public static int arraySum(int[] arr) {
        int sum = 0;
        for (int i = 0; i < arr.length; i++) {
            sum += arr[i];
        }
        return sum;
    }

    // finds max of three ints
    public static int maxVal(int num1, int num2, int num3) {
        int max = 0;

        if (num1 > num2) {
            max = num1;
        }
        else {
            max = num2;
        }
        if (num3 > max) {
            max = num3;
        }
        return max;
    }

    // adds leading zeros to a binaryString
    public static String addLeadingZerosBinary(String binaryString, int numZeros) {
        StringBuilder sb = new StringBuilder(binaryString);
        for (int i = 0; i < numZeros; i++) {
            sb.insert(0, "0");
        }
        return sb.toString();
    }

    // returns String conversion of binary to binary with ones complement
    public static String binaryOnesComplementWithReturn(String binaryString) {

        char[] newBinaryStringArray = new char[binaryString.length()];
        StringBuilder sb = new StringBuilder("");

        for (int i = 0; i < binaryString.length(); i++) {
            if (binaryString.charAt(i) == '0') {
                newBinaryStringArray[i] = '1';
            }
            else {
                newBinaryStringArray[i] = '0';
            }
        }

        for (int j = 0; j < newBinaryStringArray.length; j++) {
            sb.append(newBinaryStringArray[j]);
        }
        return sb.toString();
    }

    // returns String conversion of binary to binary with twos complement
    public static String binaryTwoComplementWithReturn(String binaryString) {
        binaryString = binaryOnesComplementWithReturn(binaryString); // converts binary to ones complement
        Stack<String> stack = new Stack<>();
        StringBuilder sb = new StringBuilder("");

        for (int i = binaryString.length() - 1; i >= 0; i--) { // starting from the rightmost bit in binaryString
            if (binaryString.charAt(i) == '0') { // If 0
                stack.push("1");
                for (int j = i - 1; j >= 0; j--) { // once a 1 is added, put the rest of the binaryString bits into the stack
                    stack.push(String.valueOf(binaryString.charAt(j)));
                }
                break;
            }
            else { // If 1
                stack.push("0");
            }
        }

        int stackSize = stack.size();

        for (int j = 0; j < stackSize; j++) {
            sb.append(stack.pop());
        }
        return sb.toString();
    }

    // return int conversion of String to integer 
    public static int strToInt(String s) {

        int returnInt = 0;

        for (int i = 0; i < s.length(); i++) {
            returnInt = returnInt * 10 + (s.charAt(i) - 48);
        }

        return returnInt;

    }

    // Converts hex value to int value 
    public static int hexToInt(char hexVal) {

        int intVal = 0;

        switch(hexVal) {
            case 'A':
            case 'a':
                intVal = 10;
                break;
            case 'B':
            case 'b':
                intVal = 11;
                break;
            case 'C':
            case 'c':
                intVal = 12;
                break;
            case 'D':
            case 'd':
                intVal = 13;
                break;
            case 'E':
            case 'e':
                intVal = 14;
                break;
            case 'F':
            case 'f':
                intVal = 15;
                break;
            default:
                intVal = strToInt(String.valueOf(hexVal));
        }
        return intVal;
    }

    // Converts int val to String hex equivalent
    public static String intToHex(int num) {
        String intAsHex = "";
        switch(num) {
            case 10:
                intAsHex = "a";
                break;
            case 11:
                intAsHex = "b";
                break;
            case 12: 
                intAsHex = "c";
                break;
            case 13:
                intAsHex = "d";
                break;
            case 14:
                intAsHex = "e";
                break;
            case 15:
                intAsHex = "f";
                break;
            default:
                intAsHex += num;
        }
        return intAsHex;
    }

    // returns String conversion of String binary number to decimal number 
    public static String binaryToDecimalWithReturn(String binaryString) {
        int decimalSum = 0;
        int position = 0;

        for (int j = binaryString.length() - 1; j > 1; j--) {
            if (String.valueOf(binaryString.charAt(j)).equals("1")) {
                decimalSum += powProduct(2, position);
            }
            position++;
        }
        return "" + decimalSum;
    }

    // returns String conversion of String hexadecimal number to decimal number 
    public static String hexToDecimalWithReturn(String hexNum) {

        int decimalSum = 0;
        int position = 0;
        int hexAsDecimalNum = 0;

        for (int i = hexNum.length() - 1; i > 1; i--) { // Working backwards...
            hexAsDecimalNum = hexToInt(hexNum.charAt(i));
            decimalSum = decimalSum + (hexAsDecimalNum * powProduct(16, position));
            position++;
        }
        return "" + decimalSum;
    }

    // return String conversion of String decimal number to binary
    public static String decimalToBinaryWithReturn(String decimalString) {
        int decimalNum = strToInt(decimalString);
        int remainder = 0;
        Stack<Integer> stack = new Stack<>();
        StringBuilder sb = new StringBuilder("");

        while (decimalNum != 0) {
            remainder = decimalNum % 2;
            decimalNum = decimalNum / 2;
            stack.push(remainder);
        }

        int stackSize = stack.size();
        for (int j = 0; j < stackSize; j++) {
            sb.append("" + stack.pop());
        }
        return sb.toString();
    }

    // returns string conversion of String hexadecimal to binary
    public static String hexToBinaryWithReturn(String hexVal) {

        Queue<Character> bitQueue = new LinkedList<>();
        int decimalVal = 0;
        StringBuilder str = new StringBuilder("");

        for (int i = 2; i < hexVal.length(); i++) {
        
            decimalVal = hexToInt(hexVal.charAt(i));

            if (decimalVal - 8 >= 0) {
                decimalVal = decimalVal - 8;
                bitQueue.add('1');
            }
            else {
                bitQueue.add('0');
            }

            if (decimalVal - 4 >= 0) {
                decimalVal = decimalVal - 4;
                bitQueue.add('1');
            }
            else {
                bitQueue.add('0');
            }

            if (decimalVal - 2 >= 0) {
                decimalVal = decimalVal - 2;
                bitQueue.add('1');
            }
            else {
                bitQueue.add('0');
            }

            if (decimalVal - 1 >= 0) {
                decimalVal = decimalVal - 1;
                bitQueue.add('1');
            }
            else {
                bitQueue.add('0');
            }
        }

        int queueSize = bitQueue.size();

        for (int i = 0; i < queueSize; i++) {
            str.append(bitQueue.remove());
        }

        return str.toString();
    }

    // returns String conversion of String decimal to hexadecimal
    public static String decimalToHexWithReturn(String decimalNum) {

        Stack<String> stack = new Stack<>();
        int decimalNumInt = strToInt(decimalNum);
        int remainder = 0;
        StringBuilder sb = new StringBuilder("");
        
        while (decimalNumInt > 0) {
            remainder = decimalNumInt % 16;
            decimalNumInt = decimalNumInt / 16;
            stack.push(intToHex(remainder));
        }

        int stackSize = stack.size();

        for (int i = 0; i < stackSize; i++) {
            sb.append(stack.pop());
        }
        return sb.toString();
    }
    

    // Main // 


    public static void main(String args[]) {

        // Task 1 //

        System.out.println("Task 1");

        if (args.length != 3) {
            System.out.println("Incorrect number of arguments have been provided. Program Terminating!");
            return;
        }
        
        System.out.println("Correct number of arguments given.");

        // Tasks 2 - 8 Execution -- See Methods for Descriptions //

        System.out.println("\nTask 2");
        printType(args);

        System.out.println("\nTask 3");
        boolean isCorrect = correctFormat(args);

        if (!(isCorrect)) { // if isCorrect returned a false boolean, then one of the args passed was bad.  Program should terminate.
            return;
        }

        System.out.println("\nTask 4");
        convertTypes(args);

        System.out.println("\nTask 5");
        onesComplement(args);

        System.out.println("\nTask 6");
        twosComplement(args);

        System.out.println("\nTask 7");
        bitwiseOperations(args);

        System.out.println("\nTask 8");
        bitShiftOperations(args);
    }
}