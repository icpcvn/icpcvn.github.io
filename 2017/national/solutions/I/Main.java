import java.io.OutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.PrintWriter;
import java.util.Arrays;
import java.util.StringTokenizer;
import java.io.IOException;
import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.InputStream;
import java.util.ArrayList;

/**
 * Built using CHelper plug-in
 * Actual solution is at the top
 *
 * @author Van Hanh Pham <skyvn97> <vanhanh.pham@gmail.com>
 */
public class Main {
    public static void main(String[] args) {
        InputStream inputStream = System.in;
        OutputStream outputStream = System.out;
        InputReader in = new InputReader(inputStream);
        PrintWriter out = new PrintWriter(outputStream);
        RotatedNumber solver = new RotatedNumber();
        int testCount = Integer.parseInt(in.next());
        for (int i = 1; i <= testCount; i++)
            solver.solve(i, in, out);
        out.close();
    }

    static class RotatedNumber {
        private static final int MAX_VALUE = (int) 1e6;
        private static final int[] PW10 = {1, 10, 100, 1000, (int) 1e4, (int) 1e5, (int) 1e6};
        private int[] minRotation;
        private int[] countMinRotation;
        private int[][] numbers;
        private ArrayList<Integer> values;

        private static int getMinRotation(int x, int len) {
            int res = x;
            for (int i = 0; i < len - 1; i++) {
                int tmp = x % 10;
                x = tmp * PW10[len - 1] + x / 10;
                if (tmp > 0) res = Math.min(res, x);
            }
            return res;
        }

        private void prepare() {
            if (minRotation != null) return;

            minRotation = new int[MAX_VALUE];

            for (int len = 1; len <= 6; len++)
                for (int val = PW10[len - 1]; val < PW10[len]; val++)
                    minRotation[val] = getMinRotation(val, len);

            countMinRotation = new int[MAX_VALUE];
            Arrays.fill(countMinRotation, 0);
            for (int x : minRotation) countMinRotation[x]++;

            numbers = new int[MAX_VALUE][];
            for (int i = 0; i < MAX_VALUE; i++)
                if (countMinRotation[i] > 1) numbers[i] = new int[countMinRotation[i]];
            for (int i = MAX_VALUE - 1; i >= 0; i--)
                if (numbers[minRotation[i]] != null) {
                    int pos = --countMinRotation[minRotation[i]];
                    numbers[minRotation[i]][pos] = i;
                }

            values = new ArrayList<Integer>();
            for (int i = 0; i < MAX_VALUE; i++)
                if (numbers[i] != null) values.add(i);
        }

        public void solve(int testNumber, InputReader in, PrintWriter out) {
            prepare();

            int a = in.nextInt();
            int b = in.nextInt();
            out.println(query(a, b));
        }

        private long query(int l, int r) {
            long res = 0;
            for (int x : values) {
                int[] cur = numbers[x];
                int L = Arrays.binarySearch(cur, l);
                if (L < 0) L = -(L + 1);
                int R = Arrays.binarySearch(cur, r + 1);
                if (R < 0) R = -(R + 1);
                res += 1L * (R - L) * (R - L - 1) / 2;
            }
            return res;
        }

    }

    static class InputReader {
        public BufferedReader reader;
        public StringTokenizer tokenizer;

        public InputReader(InputStream stream) {
            reader = new BufferedReader(new InputStreamReader(stream), 32768);
            tokenizer = null;
        }

        public String nextString() {
            while (tokenizer == null || !tokenizer.hasMoreTokens()) {
                try {
                    tokenizer = new StringTokenizer(reader.readLine());
                } catch (IOException e) {
                    throw new RuntimeException(e);
                }
            }
            return tokenizer.nextToken();
        }

        public String next() {
            return nextString();
        }

        public int nextInt() {
            return Integer.parseInt(nextString());
        }

    }
}


