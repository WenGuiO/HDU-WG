package cryptograghy;


import java.nio.charset.StandardCharsets;
import java.util.Scanner;

/**
 * DES 算法
 * @author wengui
 */
public class DES {

    /**
     * 子密钥
     */
    private static final String[] KEYS = new String[16];
    /**
     * 明文长度
     */
    private static int len;
    /**
     * 置换
     * 根据 置换表 返回 新 二进制字符串
     * @param ori   原二进制字符串
     * @param table 置换表
     * @return  置换后 新 二进制字符串
     */
    private static String permutation(String ori, int[] table){
        StringBuilder des = new StringBuilder(table.length);
        //value 遍历 table 中的值
        for (int value : table) {
            des.append(ori.charAt(value - 1));
        }
        return des.toString();
    }

    /**
     * 子密钥 生成器
     * @param key 密钥
     */
    private static void generateKeys(String  key) {

        //PC1 置换 => 56位有效秘钥
        String validKey = permutation(key, DES_Rules.PC1_TABLE);

        String l = validKey.substring(0, 28);
        String r = validKey.substring(28, 56);
        //16轮 循环移位
        for (int i = 0; i < 16; i++) {
            // 移位 ： 字符串截断拼接实现
            int j = DES_Rules.LS_TABLE[i];
            l = l.substring(j) + l.substring(0, j);
            r = r.substring(j) + r.substring(0, j);

            // 左右 56位 密钥 => PC2 置换 => 48位 子密钥
            KEYS[i] = permutation(l + r, DES_Rules.PC2_TABLE);
        }
    }

    /**
     * 16轮 迭代加密
     * @param plainText 明文
     * @param method 加/解密
     * @return 字符串
     */
    private static String round16(String plainText ,  String method){
        String left = plainText.substring(0, 32);
        String right = plainText.substring(32);
        String temp;
        if("encrypt".equals(method)){
            for (int i = 0; i < 16; i++) {
                temp = right;

                String o = feistel(right, KEYS[i]);
                //右半 部分参与运算
                right = xor(left, o);

                //原右半 部分变为 左半 部分
                left = temp;
            }
        }else if("decrypt".equals(method)){
            for (int i = 15; i >= 0; i--) {
                temp = right;
                //右半 部分参与运算
                right = xor(left, feistel(right, KEYS[i]));
                //原右半 部分变为 左半 部分
                left = temp;
            }
        }

        //循环中最后一次 左右部分 已调换
        return right + left;
    }

    /**
     * f 函数
     * @param ori 参与运算的部分
     * @param key   子密钥
     * @return 运算后 二进制字符串
     */
    private static String  feistel(String ori, String key){
        //E 拓展 => 48位
        ori = permutation(ori, DES_Rules.E_TABLE);
        //异或
        ori = xor(ori, key);
        //s 盒压缩 => 32位
        ori = sBoxCompression(ori);
        //p 盒置换
        ori = permutation(ori, DES_Rules.P_TABLE);

        return ori;
    }

    /**
     * 异或运算
     * @param str1  字符串1
     * @param str2  字符串2
     * @return  运算后字符串
     */
    private static String xor(String str1, String str2) {
        int len = str1.length();
        //安全检验
        if(str2.length() != len){
            System.out.println("xor(): 参数长度不相同");
            System.exit(0);
        }

        StringBuilder result = new StringBuilder(48);
        for (int i = 0; i < len; i++) {
            if (str1.charAt(i) == str2.charAt(i)) {
                result.append("0");
            } else {
                result.append("1");
            }
        }
        return result.toString();
    }

    /**
     * S 盒压缩
     * @param input 48位字符
     * @return  32位字符
     */
    private static String sBoxCompression(String input) {
        if(input.length() != 48){
            System.out.println("sBoxCompression(): 处理非48位字符串");
            System.exit(0);
        }

        StringBuilder des = new StringBuilder(32);
        //分组压缩
        for (int i = 0; i < 8; i++) {
            String block = input.substring(i * 6, (i + 1) * 6);
            //将 二进制 字符串转换 10进制
            int row = Integer.parseInt(String.valueOf(block.charAt(0)) + block.charAt(5), 2);
            int col = Integer.parseInt(block.substring(1, 5), 2);

            int value = DES_Rules.S_BOX[i][row][col];
            des.append(String.format("%4s", Integer.toBinaryString(value)).replace(' ', '0'));
        }
        return des.toString();
    }

    /**
     * 加密
     *
     * @param plaintext 明文
     * @param key 密钥
     * @return 密文
     */
    public static String encrypt(String plaintext, String key){
        /*
        // 以下设计便于外部 调用
         */
        if(plaintext.length() > 8 || key.length() > 8){
            System.out.println("明文/秘钥 须在8个字节以内 !");
            System.exit(0);
        }
        //预处理： 转换二进制字符串，位数填充
        plaintext = preHandle(plaintext);
        key = preHandle(key);

        //子密钥生成
        generateKeys(key);

        plaintext = round16(permutation(plaintext, DES_Rules.IP_TABLE), "encrypt");

        return permutation(plaintext, DES_Rules.IPINV_TABLE);
    }

    /**
     * 解密
     *
     * @param ciphertext 密文
     * @param key 密钥
     * @return 明文
     */
    private static String  decrypt(String ciphertext, String key){
        /*
        // 考以下设计便于外部 调用
         */
        if(ciphertext.length() != 64 ){
            //这里可填充多个验证函数，本处暂不实现
            System.out.println("密文不符合要求(非64位，非0-1字符串) !");
            System.exit(0);
        }
        if( key.length() > 8){
            System.out.println("秘钥 须在8个字节以内 !");
            System.exit(0);
        }
        //长远考虑：便于外部可直接传入 密文 和 key 调用，所以重复处理
        //预处理： 转换二进制字符串，位数填充
        key = preHandle(key);

        //子密钥生成
        generateKeys(key);
        ciphertext = round16(permutation(ciphertext, DES_Rules.IP_TABLE), "decrypt");

        return permutation(ciphertext, DES_Rules.IPINV_TABLE);
    }

    /**
     * 二进制字符串 转换 字符字符串
     * @param ori 二进制字符串
     * @return  字符字符串
     */
    private static String binaryToString(String ori) {
        int length = ori.length()/8;
        StringBuilder result = new StringBuilder(length);
        for (int i = 0; i < length; i++) {
            String b = ori.substring(i*8, (i+1)*8);
            // 将二进制字符串转换为十进制整数
            int decimal = Integer.parseInt(b, 2);
            // 将整数转换为字符
            char character = (char) decimal;

            result.append(character);
        }
        return result.substring(0,len);
    }

    /**
     * 字符预处理
     * 转换二进制字符串， 补足位数
     * @param ori 原字符串
     * @return 64位二进制字符串
     */
    private static String preHandle(String ori){
        // 64位初始秘钥  二进制字符串
        StringBuilder binaryString = new StringBuilder(64);

        byte[] bytes = ori.getBytes(StandardCharsets.UTF_8);
        for (byte aByte : bytes) {
            //转换 二进制
            String bitStr = Integer.toBinaryString(aByte);
            //确定 补0 位数
            int len = 8 - bitStr.length();
            if (len > 0) {
                bitStr = String.format("%0" + len + "d", 0) + bitStr;
            }

            binaryString.append(bitStr);
        }
        // 补齐64位
        while (binaryString.length() < 64) {
            binaryString.append(String.format("%08d", 0));
        }

        return binaryString.toString();
    }

    /**
     * 主函数
     * @param args 参
     */
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        System.out.print("请输入明文:\t");
        String plainText = scanner.next();
        //便于测试观察
        System.out.println("明文转换(0-1):" + preHandle(plainText));
        //记录明文长度，便于解码转换
        len = plainText.length();

        System.out.print("请输入秘钥:\t");
        String key = scanner.next();

        String cipher = encrypt(plainText, key);
        System.out.println("加密结果(0-1): " + cipher);
        System.out.println("加密结果：" + binaryToString(cipher));

        String decryptText = decrypt(cipher, key);
        System.out.println("解密结果(0-1)："+decryptText);
        System.out.println("解密结果：" + binaryToString(decryptText));
    }

}

