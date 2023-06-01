package cryptograghy;

import java.math.BigInteger;
import java.util.Random;
import java.util.Scanner;

/**
 * RSA密码
 * @author wengui
 */
public class RSA {
    public static final Random random = new Random();
    /**
     * 密钥长度，一般为1024位或2048位
     */
    public static final  int BIT_LENGTH = 1024;
    /**
     * 素性检测的精度
     */
    public static final  int CERTAINTY = 15;


    /**
     * 素数检测
     * @param n 数
     * @param checkCount 精度
     * @return ture/false
     */
    public static boolean isPrime(BigInteger n, int checkCount) {
        // 排除小于等于 1 的数
        if (n.compareTo(BigInteger.ONE) <= 0) {
            return false;
        }

        //若为 2 --> ture
        if(n.compareTo(BigInteger.valueOf(2)) == 0 ){
            return true;
        }

        //若被 2 整除或为 1 --> false
        if (n.mod(BigInteger.TWO).equals(BigInteger.ZERO) || n.compareTo(BigInteger.ONE) == 0) {
            return false;
        }

        //将n - 1写成 2^s * d 形式
        BigInteger d = n.subtract(BigInteger.ONE);
        int s = 0;
        while (d.mod(BigInteger.TWO).equals(BigInteger.ZERO)) {
            //s记录偶数因子的个数，
            s++;
            //d为 n - 1 除以 2^s 后得到的奇数。
            d = d.divide(BigInteger.TWO);
        }
        /*
        上面步骤的目的是为了方便进行下一步的计算。根据算法步骤，需要随机选取一个整数a，计算 a^d mod n，其中 d为一个奇数。
        将n - 1写成 2^s * d 形式后，就可以将 a^d mod n 的计算拆分成多个步骤，从而避免直接对大整数进行幂运算，提高计算效率。
        首先计算a^(d/2) mod n，然后再将结果平方取模n，得到a^d mod n的值，计算复杂度为O(log n)，
        比直接计算 a^d mod n的复杂度O(n)要小得多。
         */

        //Miller-Rabin素性检测
        for (int i = 0; i < checkCount; i++) {
            //随机选取一个 a, add(BigInteger.ONE) +1, 确保a是一个正整数
            BigInteger a = new BigInteger(n.bitLength() - 1, random).add(BigInteger.ONE);
            //x = a^d mod n
            BigInteger x = a.modPow(d, n);
            //若 x == 1或 n - 1
            if (x.equals(BigInteger.ONE) || x.equals(n.subtract(BigInteger.ONE))) {
                //n可能是素数，继续检测下一个a
                continue;
            }
            //素性标记
            boolean isPrime = false;
            //计算x^2 mod n、x^4 mod n、x^8 mod n ...
            for (int j = 0; j < s - 1; j++) {
                //x = x^2 mod n
                x = x.modPow(BigInteger.TWO, n);
                //若 x = n - 1
                if (x.equals(n.subtract(BigInteger.ONE))) {
                    //不是素数
                    isPrime = true;
                    break;
                }
            }
            if (!isPrime) {
                return false;
            }
        }
        return true;
    }

    /**
     * 求最大公因数
     * @param a 参1
     * @param b 参2
     * @return 最小公倍数
     */
    private static BigInteger gcd(BigInteger a, BigInteger b) {
        if (b.equals(BigInteger.ZERO)) {
            return a;
        } else {
            return gcd(b, a.mod(b));
        }
    }

    /**
     * 生成e，满足1 < e < φ(n) 且 e 与 φ(n)互质
     * @param phi 欧拉函数值
     * @param bitLength e的位长
     * @return 生成的e值
     */
    private static BigInteger generateE(BigInteger phi, int bitLength) {
        BigInteger e;
        do {
            e = new BigInteger(bitLength, random);
            //若 e 小于0, 大于 φ(n), 与 φ(n) gcd 不等于1 --> 重新生成
        } while (e.compareTo(BigInteger.ONE) <= 0 || e.compareTo(phi) >= 0 || !gcd(e, phi).equals(BigInteger.ONE));
        return e;
    }

    /**
     * 求 d
     * @param e 私钥
     * @param phi φ(n)
     * @return 公钥
     */
    private static BigInteger generateD(BigInteger e, BigInteger phi) {
        return e.modInverse(phi);
    }

    /**
     * 大素数生成
     * @param bitLength 比特长度
     * @return 大素数
     */
    private static BigInteger generatePrimes(int bitLength){
        /*
        //方式1: 自定义随机生成
        BigInteger p;
        do {
            p = new BigInteger(bitLength, random);
        } while (!isPrime(p, CERTAINTY));

        return p;
        */

        //方式2: 借用 BigInteger 的素数生成, 与方式1 差不多
        return BigInteger.probablePrime(bitLength, random);
    }

    /**
     * 加密
     * @param message 明文
     * @param n 公钥的n
     * @param e 公钥的e
     * @return 密文
     */
    public static byte[] encrypt(byte[] message, BigInteger n, BigInteger e) {
        //转换为大整数, 1表示为正数
        BigInteger m = new BigInteger(1, message);
        // c = m ^ e mod n
        BigInteger c = m.modPow(e, n);
        return c.toByteArray();
    }

    /**
     * 解密
     * @param ciphertext 密文
     * @param n 私钥的n
     * @param d 私钥的d
     * @return 明文
     */
    public static byte[] decrypt(byte[] ciphertext, BigInteger n, BigInteger d) {
        BigInteger c = new BigInteger(1, ciphertext);
        // m = c ^ d mod n
        BigInteger m = c.modPow(d, n);
        return m.toByteArray();
    }

    /**
     * 外部测试
     */
    public static void test() {
        Scanner sc = new Scanner(System.in);

        BigInteger p = generatePrimes(BIT_LENGTH);
        BigInteger q = generatePrimes(BIT_LENGTH);
        System.out.println("p = " + p);
        System.out.println("q = " + q);

        // 计算n
        BigInteger n = p.multiply(q);
        // 计算 φ(n)
        BigInteger phi = p.subtract(BigInteger.ONE).multiply(q.subtract(BigInteger.ONE));
        System.out.println("φ(n) = " + phi);

        // 生成e
        BigInteger e = generateE(phi, BIT_LENGTH);
        // 计算d
        BigInteger d = generateD(e, phi);

        System.out.println("\n公钥(n, e):");
        System.out.println("\tn = " + n);
        System.out.println("\te = " + e);
        System.out.println("私钥(n, d):");
        System.out.println("\tn = " + n);
        System.out.println("\td = " + d);

        System.out.print("\n请输入明文: ");
        String message = sc.next();
        // 加密
        byte[] ciphertext = encrypt(message.getBytes(), n, e);
        System.out.println("\n密文: " + new String(ciphertext));

        // 解密
        byte[] plaintext = decrypt(ciphertext, n, d);
        System.out.println("\n明文: " + new String(plaintext));
    }

    public static void main(String[] args) {
        test();
    }

}
