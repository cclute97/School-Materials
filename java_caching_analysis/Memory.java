
package cs250.hw2;

import java.util.Random;
import java.util.TreeSet;
import java.util.LinkedList;

public class Memory {

    private static volatile int volCounter; // This is our Volatile Counter

    // HELPER METHODS // 

    // Task 01 Helpers

    public static long nonVolatileLoop(int size) {

        long runningTotal = 0;

        for (int i = 0; i < size; i++) {
            if (i % 2 == 0) {
                runningTotal += i;
            }
            else {
                runningTotal -= i;
            }
        }
        return runningTotal;
    }
    
    public static long volatileLoop(int size) {

        long runningTotal = 0;

        for (volCounter = 0; volCounter < size; volCounter++) {
            if (volCounter % 2 == 0) {
                runningTotal += volCounter;
            }
            else {
                runningTotal -= volCounter;
            }
        }
        return runningTotal;
    }

    public static double getNonVolatileLoopElapsedTime(int size, int experiments) {

        double elapsedTime = 0.0;

        for (int i = 0; i < experiments; i++) {
            long start = System.nanoTime();
            nonVolatileLoop(size);
            long stop = System.nanoTime();
            elapsedTime += (stop - start);
        }

        return elapsedTime / 1000000000;
    }

    public static double getVolatileLoopElapsedTime(int size, int experiments) {
        
        double elapsedTime = 0.0;

        for (int i = 0; i < experiments; i++) {
            long start = System.nanoTime();
            volatileLoop(size);
            long stop = System.nanoTime();
            elapsedTime += (stop - start);
        }

        return elapsedTime / 1000000000;
    }

    public static double calcAverageTimeNonVolatile(int size, int experiments) {
        return getNonVolatileLoopElapsedTime(size, experiments) / experiments; 
    }

    public static double calcAverageTimeVolatile(int size, int experiments) {
        return getVolatileLoopElapsedTime(size, experiments) / experiments;
    }

    public static double calcNonVolatileAverageSum(int size, int experiments) {
        long sum = 0;
        for (int i = 0; i < experiments; i++) {
            sum += nonVolatileLoop(size);
        }
        
        return (sum / (double) experiments);
    }

    public static double calcVolatileAverageSum(int size, int experiments) {
        long sum = 0;
        for (int i = 0; i < experiments; i++) {
            sum += volatileLoop(size);
        }
        
        return (sum / (double) experiments);
    }

    // Task 02 Helpers

    public static Integer[] createRandomNumArray(int size, Random randomNumGen) {
        Integer[] randomNumArray = new Integer[size];
        for (int i = 0; i < size; i++) {
            randomNumArray[i] = randomNumGen.nextInt();
        }
        return randomNumArray;
    }

    public static double[] getKnownElementAccessTimeAndSum(Integer[] array) {
        int firstTenPercent = (int)(array.length * 0.10);
        double[] knownElementAccessTimeAndSum = {0.0, 0.0}; // [0] = time, [1] = sum total

        for (int i = 0; i < firstTenPercent; i++) {
            long start = System.nanoTime();
            knownElementAccessTimeAndSum[1] += array[i];
            long stop = System.nanoTime();
            knownElementAccessTimeAndSum[0] += (stop - start);
        }

        return knownElementAccessTimeAndSum;
    }

    public static double[] getRandomElementAccessTimeAndNumber(Integer[] array, Random randomNumGen) {
        int lastTenPercentStartIndex = (int)(array.length * 0.90);
        double[] accessTimeAndNumber = {0.0, 0.0}; // [0] = time, [1] = number
        int randomNum = randomNumGen.nextInt(array.length - lastTenPercentStartIndex) + lastTenPercentStartIndex;

        long start = System.nanoTime();

        accessTimeAndNumber[1] = array[randomNum]; // our random number    

        long stop = System.nanoTime();

        accessTimeAndNumber[0] = stop - start; // our access time

        return accessTimeAndNumber;
    }

    // Task 03 Helpers

    public static TreeSet<Integer> createTreeSetOfRange(int size) {
        TreeSet<Integer> tree = new TreeSet<>();

        for (int i = 0; i < size; i++) {
            tree.add(i);
        }

        return tree;
    }

    public static LinkedList<Integer> createLinkedListOfRange(int size) {
        LinkedList<Integer> linkedList = new LinkedList<>();

        for (int i = 0; i < size; i++) {
            linkedList.add(i);
        }

        return linkedList;
    }

    public static double getTreeSetSearchTime(TreeSet<Integer> treeSet, int randomNum) {
        long start = System.nanoTime();

        treeSet.contains(randomNum);

        long stop = System.nanoTime();

        return (double) (stop - start);
    }

    public static double getLinkedListSearchTime(LinkedList<Integer> linkedList, int randomNum) {
        long start = System.nanoTime();

        linkedList.contains(randomNum);

        long stop = System.nanoTime();

        return (double) (stop - start);
    }


    // TASK METHODS //


    public static void task01(int size, int experiments) {
        System.out.println("Task 1");
        System.out.printf("Regular: %.5f %s%n", calcAverageTimeNonVolatile(size, experiments), "seconds");
        System.out.printf("Volatile: %.5f %s%n", calcAverageTimeVolatile(size, experiments), "seconds");
        System.out.printf("Avg regular sum: %.2f%n", calcNonVolatileAverageSum(size, experiments));
        System.out.printf("Avg volatile sum: %.2f%n", calcVolatileAverageSum(size, experiments));
        System.out.println();
    }

    public static void task02(int size, int experiments, int seed) {
        Random randomNumGen = new Random(seed);
        Integer[] randomNumArray = createRandomNumArray(size, randomNumGen);
        
        double knownElementAccessTimeTotal = 0.00;
        double[] knownElementAccessTimeAndSum = new double[2]; // [0] = time, [1] = sum
        double randomElementAccessTimeTotal = 0.00;
        double[] randomElementAccessTimeAndNumber = new double[2]; // [0] = time, [1] = number
        double sumAllElements = 0.00;
        
        for (int i = 0; i < experiments; i++) {
            knownElementAccessTimeAndSum = getKnownElementAccessTimeAndSum(randomNumArray);
            knownElementAccessTimeTotal += knownElementAccessTimeAndSum[0];
            randomElementAccessTimeAndNumber = getRandomElementAccessTimeAndNumber(randomNumArray, randomNumGen);
            randomElementAccessTimeTotal += randomElementAccessTimeAndNumber[0];
            sumAllElements += randomElementAccessTimeAndNumber[1] + knownElementAccessTimeAndSum[1];
        }

        System.out.println("Task 2");
        System.out.printf("Average time to access known element: %.2f %s%n", (knownElementAccessTimeTotal / (randomNumArray.length * 0.10)) / experiments, "nanoseconds");
        System.out.printf("Average time to access random element: %.2f %s%n", randomElementAccessTimeTotal / experiments, "nanoseconds");
        System.out.printf("Sum: %.2f%n", sumAllElements / experiments);
        System.out.println();
    }

    public static void task03(int size, int experiments) {
        TreeSet<Integer> treeSet = createTreeSetOfRange(size);
        LinkedList<Integer> linkedList = createLinkedListOfRange(size);
        Random random = new Random();

        double totalElapsedTimeTreeSetContains = 0.0;
        double totalElapsedTimeLinkedListContains = 0.0;

        for (int i = 0; i < experiments; i++) {
            int randomNum = random.nextInt(size);
            totalElapsedTimeTreeSetContains += getTreeSetSearchTime(treeSet, randomNum);
            totalElapsedTimeLinkedListContains += getLinkedListSearchTime(linkedList, randomNum);
        }

        System.out.println("Task 3");
        System.out.printf("Avg time to find in set: %.2f %s%n", (totalElapsedTimeTreeSetContains / experiments), "nanoseconds");
        System.out.printf("Avg time to find in list: %.2f %s%n", (totalElapsedTimeLinkedListContains / experiments), "nanoseconds");
        System.out.println("");
    }

    public static void main(String[] args) { // takes 3 args: size [0], experiments [1], and seed [2]

        int arg1 = Integer.parseInt(args[0]); // Size
        int arg2 = Integer.parseInt(args[1]); // Experiments
        int arg3 = Integer.parseInt(args[2]); // Seed

        task01(arg1, arg2);
        task02(arg1, arg2, arg3);
        task03(arg1, arg2);
    }
}