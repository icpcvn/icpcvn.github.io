// Author: RR
// Brute force with priority

import java.io.*;
import java.util.*;
import java.math.*;

public class RR {
    public static void main(String[] args) {
        InputReader in = new InputReader(System.in);
        PrintWriter out = new PrintWriter(System.out);

        (new Solver()).go(in, out);

        out.close();
    }
}

class Solver {
    int m, n;
    char[][] board, orig;

    public void go(InputReader in, PrintWriter out) {
        m = in.nextInt();
        n = in.nextInt();
        
        board = new char[m + 2][n + 2];
        orig = new char[m + 2][n + 2];

        for (int i = 0; i < m+2; i++) {
            Arrays.fill(board[i], ' ');
        }

        for (int i = 1; i <= m; i++) {
            String s = in.next();
            for (int j = 1; j <= n; j++)
                board[i][j] = s.charAt(j - 1);
        }

        for (int i = 0; i < m+2; i++) {
            for (int j = 0; j < n+2; j++) {
                orig[i][j] = board[i][j];
            }
        }

        try {
            attempt(0);
        } catch (Exception ex) {
            for (int i = 1; i <= m; i++) {
                for (int j = 1; j <= n; j++) {
                    if (isDigit(board[i][j])) out.print(orig[i][j]);
                    else out.print(board[i][j]);
                }
                out.println();
            }
        }
    }

    final int[] DI = {-1, 1, 0, 0};
    final int[] DJ = {0, 0, -1, 1};
    final char[] DV = {'v', '^', '>', '<'};

    void attempt(int depth) throws Exception {
        int savei = -1, savej = -1;

        final int MAX = 99;
        int minOptions = MAX;
        int maxExtension = 0;

        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= m; j++) {
                if (board[i][j] == '.') {
                    int options = 0;
                    int extension = MAX;

                    for (int dir = 0; dir < 4; dir++) {
                        int need = 1;
                        for (int ii = i + DI[dir], jj = j + DJ[dir];
                                inside(ii, jj); ii += DI[dir], jj += DJ[dir]) {
                            char cur = board[ii][jj];
                            if (isDigit(cur)) {
                                int val = cur - '0';
                                if (val >= need) {
                                    ++options;
                                    extension = Math.min(extension, need);
                                }
                                break;
                            }

                            if (cur == '.') ++need;
                            if (cur != '.' && cur != DV[dir]) break;
                        }
                    }

                    if (options < minOptions
                            || (options == minOptions && extension > maxExtension)) {
                        savei = i;
                        savej = j;
                        minOptions = options;
                        maxExtension = extension;
                    }
                }
            }
        }

        if (minOptions == 0) {
            // No solution.
            return ;
        }

        if (minOptions == MAX) {
            // Found solution.
            throw new Exception();
        }

        int i = savei, j = savej;
        char[][] save = new char[15][15];

        for (int dir = 0; dir < 4; dir++) {
            int need = 1;
            for (int ii = i + DI[dir], jj = j + DJ[dir];
                    inside(ii, jj); ii += DI[dir], jj += DJ[dir]) {
                char cur = board[ii][jj];
                if (isDigit(cur)) {
                    int val = cur - '0';
                    if (val >= need) {
                        for (int x = i, y = j; x != ii || y != jj;
                                x += DI[dir], y += DJ[dir]) {
                            save[x][y] = board[x][y];
                            board[x][y] = DV[dir];
                        }
                        save[ii][jj] = board[ii][jj];
                        board[ii][jj] -= need;

                        attempt(depth + 1);
                        for (int x = i, y = j; x != ii || y != jj;
                                x += DI[dir], y += DJ[dir]) {
                            board[x][y] = save[x][y];
                        }
                        board[ii][jj] = save[ii][jj];
                    }
                    break;
                }
                if (cur == '.') ++need;
                if (cur != '.' && cur != DV[dir]) break;
            }
        }
    }

    boolean inside(int i, int j) {
        return 1 <= i && i <= m && 1 <= j && j <= n;
    }

    boolean isDigit(char c) {
        return c >= '0' && c <= '9';
    }
}

class InputReader {
    public BufferedReader reader;
    public StringTokenizer tokenizer;

    public InputReader(InputStream stream) {
        reader = new BufferedReader(new InputStreamReader(stream), 32768);
        tokenizer = null;
    }

    public String next() {
        while (tokenizer == null || !tokenizer.hasMoreTokens()) {
            try {
                tokenizer = new StringTokenizer(reader.readLine());
            } catch (IOException e) {
                throw new RuntimeException(e);
            }
        }
        return tokenizer.nextToken();
    }

    public int nextInt() {
        return Integer.parseInt(next());
    }

}

