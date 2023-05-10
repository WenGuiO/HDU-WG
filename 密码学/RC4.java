package cryptograghy;

import java.util.Scanner;

/**
 * RC4密码
 * @author wengui
 */
public class RC4 {
    
    public final  static int  SBOX_LENGHT =  256;
    
    /**
     *  伪随机 S 盒生成器
     * @param key   密钥
     * @return  S盒 char[]
     */
    public static char[] generateSBox(char[] key) {
        char[] sBox = new char[256];
        int kLen = key.length - 1;

        for (int i = 0; i < 256; i++) {
            sBox[i] = (char) i;
        }

        int j = 0;
        for (int i = 0; i < 256; i++) {
            j = (j + sBox[i] + key[i & kLen]) & 0xFF;
            swap(sBox, i, j);
        }

        return sBox;
    }


    /**
     *  数组元素交换
     * @param arr   目标数组
     * @param i 参数1
     * @param j 参数2
     */
    private static void swap(char[] arr, int i, int j) {
        char temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
    }

    /**
     *  密钥流生成器
     * @param sBox  S盒
     * @param mSize 明文长度
     * @return  密钥流 char[]
     */
    public static char[] generateKeyStream(char[] sBox, int mSize) {
        char[] keyStream = new char[mSize];
        int i = 0, j = 0;

        //使用 位运算 代替 模运算
        for (int k = 0; k < mSize; k++) {
            i = (i + 1) & 0xff;
            j = (j + sBox[i]) & 0xff;
            swap(sBox, i, j);
            keyStream[k] = sBox[(sBox[i] + sBox[j]) & 0xff];
        }

        return keyStream;
    }

    /**
     *  RC4 加密
     * @param plainText 明文
     * @param keyStream 密钥流
     * @return  密文  chat[]
     */
    public static char[] encipher(char[] plainText, char[] keyStream) {
        int len = plainText.length;
        char[] ciphertext = new char[len];
        //同位亦或运算
        for (int i = 0; i < len; i++) {
            ciphertext[i] = (char) (plainText[i] ^ keyStream[i]);
        }

        return ciphertext;
    }

    /**
     *  RC4  解密
     * @param ciphertext    密文
     * @param keyStream     密钥流
     * @return 明文  char[]
     */
    public  static char[] decipher(char[] ciphertext, char[] keyStream){
        return encipher(ciphertext, keyStream);
    }

    /**
     *  启动
     */
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        System.out.print("Enter plaintext: ");
        char[] plaintext = scanner.nextLine().toCharArray();

        System.out.println("plaintext(0-1): ");
        for (char c : plaintext) {
            //此处使用 format 是因为Integer会默认把前导的 0 舍去
            System.out.print(String.format("%8s", Integer.toBinaryString(c)).replace(' ', '0') + " ");
        }
        System.out.println();


        System.out.print("Enter key: ");
        char[] key = scanner.next().toCharArray();


        char[] sBox = generateSBox(key);
        char[] keyStream = generateKeyStream(sBox, plaintext.length);
        char[] ciphertext = encipher(plaintext, keyStream);
        char[] decryptedText = decipher(ciphertext, keyStream);

        String keySStr = new String(keyStream);
        System.out.println("keyStream --> " + keySStr);
        System.out.println("keyStream(0-1): ");
        for (char c : keySStr.toCharArray()) {
            System.out.print(String.format("%8s", Integer.toBinaryString(c)).replace(' ', '0') + " ");
        }
        System.out.println("\n");


        String cipherStr = new String(ciphertext);
        System.out.println("Ciphertext --> " + cipherStr);
        System.out.println("Ciphertext(0-1): ");
        for (char c : cipherStr.toCharArray()) {
            System.out.print(String.format("%8s", Integer.toBinaryString(c)).replace(' ', '0') + " ");
        }
        System.out.println("\n");

        String decrypStr = new String(decryptedText);
        System.out.println("Decrypted text --> " + decrypStr);
        System.out.println("Decrypted text(0-1): ");
        for (char c : decrypStr.toCharArray()) {
            System.out.print(String.format("%8s", Integer.toBinaryString(c)).replace(' ', '0') + " ");
        }
        System.out.println("\n");

    }

}
