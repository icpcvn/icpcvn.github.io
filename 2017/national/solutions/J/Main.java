import java.io.OutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.PrintWriter;
import java.util.StringTokenizer;
import java.io.IOException;
import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.InputStream;

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
        JewelryBox solver = new JewelryBox();
        int testCount = Integer.parseInt(in.next());
        for (int i = 1; i <= testCount; i++)
            solver.solve(i, in, out);
        out.close();
    }

    static class JewelryBox {
        public void solve(int testNumber, InputReader in, PrintWriter out) {
            int x = in.nextInt();
            int y = in.nextInt();
            out.printf("%.11f\n", solve(x, y));
        }

        private double solve(double x, double y) {
            double a = x;
            double b = 2 * (x - y);
            double c = -y;

            double delta = Math.max(0.0, b * b - 4 * a * c);
            double rate = (-b + Math.sqrt(delta)) / (2.0 * a);

            double h = y / (2 * rate + 4);
            return (x - 2 * h) * (y - 2 * h) * h;
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


