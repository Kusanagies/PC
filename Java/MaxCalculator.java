
public class MaxCalculator {
    private static final int N = 75000;
    private static int K;
    private static double[] tabMax;
    private static int[] tabX;
    private static int[] tabY;
    private static Thread[] threads;

    public static void init(String[] args) {
        if (args.length < 1) {
            System.out.println("Usage: java MaxCalculator <number_of_threads>");
            System.exit(1);
        }
        try {
            K = Integer.parseInt(args[0]);
        } catch (NumberFormatException e) {
            System.out.println("The argument must be an integer.");
            System.exit(1);
        }
        tabMax = new double[K];
        tabX = new int[K];
        tabY = new int[K];
        threads = new Thread[K];
    }

    public static void main(String[] args) {
        init(args);

        // Start threads
        for (int i = 0; i < K; i++) {
            final int index = i;
            Runnable task = () -> {
                System.out.printf("Thread %d started%n", index);
                for (int x = index; x <= N; x += K) {
                    for (int y = 0; y <= N; y++) {
                        double cal = f(x, y);
                        if (Math.abs(cal) > tabMax[index]) {
                            tabMax[index] = Math.abs(cal);
                            tabX[index] = x;
                            tabY[index] = y;
                        }
                    }
                }
            };
            threads[index] = new Thread(task);
            threads[index].start();
        }

        // Wait for all threads to finish
        for (int i = 0; i < K; i++) {
            try {
                threads[i].join();
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }

        // Find the global maximum
        double max = 0;
        int x = 0, y = 0;
        for (int i = 0; i < K; i++) {
            if (tabMax[i] > max) {
                max = tabMax[i];
                x = tabX[i];
                y = tabY[i];
            }
        }
        System.out.printf("The maximum is reached at (x=%d, y=%d) and is %.2f%n", x, y, max);
    }

    // Example function f(x, y)
    private static double f(int x, int y) {
        // Example: A simple function to test the logic
        return Math.sin(x * 0.001) * Math.cos(y * 0.001);
    }
}
