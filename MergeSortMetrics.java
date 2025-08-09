import java.lang.management.ManagementFactory;
import java.lang.management.ThreadMXBean;
import java.util.Random;

public class MergeSortMetrics {

    // Merge sort implementation
    public static void mergeSort(int[] array) {
        if (array.length > 1) {
            int mid = array.length / 2;

            int[] left = new int[mid];
            int[] right = new int[array.length - mid];

            System.arraycopy(array, 0, left, 0, mid);
            System.arraycopy(array, mid, right, 0, array.length - mid);

            mergeSort(left);
            mergeSort(right);

            merge(array, left, right);
        }
    }

    public static void merge(int[] result, int[] left, int[] right) {
        int i = 0, j = 0, k = 0;
        while (i < left.length && j < right.length) {
            if (left[i] <= right[j]) {
                result[k++] = left[i++];
            } else {
                result[k++] = right[j++];
            }
        }
        while (i < left.length) {
            result[k++] = left[i++];
        }
        while (j < right.length) {
            result[k++] = right[j++];
        }
    }

    public static void main(String[] args) {
        int size = 1_000_000; // Array size
        int[] array = new int[size];
        Random rand = new Random();

        for (int i = 0; i < size; i++) {
            array[i] = rand.nextInt(size);
        }

        // Get CPU time bean
        ThreadMXBean bean = ManagementFactory.getThreadMXBean();
        if (!bean.isCurrentThreadCpuTimeSupported()) {
            System.out.println("CPU time measurement not supported");
            return;
        }

        // Measure memory before
        Runtime runtime = Runtime.getRuntime();
        runtime.gc();
        long beforeUsedMem = runtime.totalMemory() - runtime.freeMemory();

        // Start timers
        long startTime = System.nanoTime();
        long startCpuTime = bean.getCurrentThreadCpuTime();

        // Perform merge sort
        mergeSort(array);

        // End timers
        long endCpuTime = bean.getCurrentThreadCpuTime();
        long endTime = System.nanoTime();

        // Measure memory after
        long afterUsedMem = runtime.totalMemory() - runtime.freeMemory();

        // Calculate metrics
        double executionTimeSec = (endTime - startTime) / 1_000_000_000.0;
        double cpuTimeSec = (endCpuTime - startCpuTime) / 1_000_000_000.0;
        double memoryUsedMB = (afterUsedMem - beforeUsedMem) / (1024.0 * 1024.0);

        System.out.println("Execution Time (seconds): " + executionTimeSec);
        System.out.println("CPU Time (seconds): " + cpuTimeSec);
        System.out.println("Memory Used (MB): " + memoryUsedMB);
    }
}


/* Java performed merge sort efficiently, completing the operation with an exceution time in under 2 seconds
 and using ~49.5 MB of memory.The code was verbose but predictable,
   and Java handled the recursion well without any stability issues. */