package cryptograghy;

import java.util.Scanner;

/**
 * SM4
 * @author wengui
 */
public class SM4 {
    /**
     * 子密钥
     */
    private static final int [] RK = new int[32];
    private static final int [] FK = {0xa3b1bac6, 0x56aa3350, 0x677d9197, 0xb27022dc};
    private static final int [] CK = {
            0x00070e15, 0x1c232a31, 0x383f464d, 0x545b6269,
            0x70777e85, 0x8c939aa1, 0xa8afb6bd, 0xc4cbd2d9,
            0xe0e7eef5, 0xfc030a11, 0x181f262d, 0x343b4249,
            0x50575e65, 0x6c737a81, 0x888f969d, 0xa4abb2b9,
            0xc0c7ced5, 0xdce3eaf1, 0xf8ff060d, 0x141b2229,
            0x30373e45, 0x4c535a61, 0x686f767d, 0x848b9299,
            0xa0a7aeb5, 0xbcc3cad1, 0xd8dfe6ed, 0xf4fb0209,
            0x10171e25, 0x2c333a41, 0x484f565d, 0x646b7279
    };

    private static final int [] S_BOX = {
            0xd6,0x90,0xe9,0xfe,0xcc,0xe1,0x3d,0xb7,0x16,0xb6,0x14,0xc2,0x28,0xfb,0x2c,0x05,
            0x2b,0x67,0x9a,0x76,0x2a,0xbe,0x04,0xc3,0xaa,0x44,0x13,0x26,0x49,0x86,0x06,0x99,
            0x9c,0x42,0x50,0xf4,0x91,0xef,0x98,0x7a,0x33,0x54,0x0b,0x43,0xed,0xcf,0xac,0x62,
            0xe4,0xb3,0x1c,0xa9,0xc9,0x08,0xe8,0x95,0x80,0xdf,0x94,0xfa,0x75,0x8f,0x3f,0xa6,
            0x47,0x07,0xa7,0xfc,0xf3,0x73,0x17,0xba,0x83,0x59,0x3c,0x19,0xe6,0x85,0x4f,0xa8,
            0x68,0x6b,0x81,0xb2,0x71,0x64,0xda,0x8b,0xf8,0xeb,0x0f,0x4b,0x70,0x56,0x9d,0x35,
            0x1e,0x24,0x0e,0x5e,0x63,0x58,0xd1,0xa2,0x25,0x22,0x7c,0x3b,0x01,0x21,0x78,0x87,
            0xd4,0x00,0x46,0x57,0x9f,0xd3,0x27,0x52,0x4c,0x36,0x02,0xe7,0xa0,0xc4,0xc8,0x9e,
            0xea,0xbf,0x8a,0xd2,0x40,0xc7,0x38,0xb5,0xa3,0xf7,0xf2,0xce,0xf9,0x61,0x15,0xa1,
            0xe0,0xae,0x5d,0xa4,0x9b,0x34,0x1a,0x55,0xad,0x93,0x32,0x30,0xf5,0x8c,0xb1,0xe3,
            0x1d,0xf6,0xe2,0x2e,0x82,0x66,0xca,0x60,0xc0,0x29,0x23,0xab,0x0d,0x53,0x4e,0x6f,
            0xd5,0xdb,0x37,0x45,0xde,0xfd,0x8e,0x2f,0x03,0xff,0x6a,0x72,0x6d,0x6c,0x5b,0x51,
            0x8d,0x1b,0xaf,0x92,0xbb,0xdd,0xbc,0x7f,0x11,0xd9,0x5c,0x41,0x1f,0x10,0x5a,0xd8,
            0x0a,0xc1,0x31,0x88,0xa5,0xcd,0x7b,0xbd,0x2d,0x74,0xd0,0x12,0xb8,0xe5,0xb4,0xb0,
            0x89,0x69,0x97,0x4a,0x0c,0x96,0x77,0x7e,0x65,0xb9,0xf1,0x09,0xc5,0x6e,0xc6,0x84,
            0x18,0xf0,0x7d,0xec,0x3a,0xdc,0x4d,0x20,0x79,0xee,0x5f,0x3e,0xd7,0xcb,0x39,0x48
    };

    private static int len;

    /**
     * 主加/解密函数
     * @param ori 明/密文
     * @param method 指定方法
     * @return 加/解密结果
     */
    private static byte[] cryptMainFunc(byte[] ori, int method) {
        //用于存储运算数据
        int[] xTemp = new int[4];
        //将输入以32比特分组
        for (int i = 0; i < 4; i++) {
            xTemp[i] = byte4ToBit32(ori[4 * i], ori[4 * i + 1], ori[4 * i + 2], ori[4 * i + 3]);
        }
        //盒变换输入和输出
        int boxIn, boxOut;

        if(method == 1){
            for (int i = 0; i < 32; i++) {
                //方法2：通过改变顺序改变模式,但每次循环都计算，弃用
                //int index = (method == 0) ? i : (31 - i);

                //sBox_input= X(i+1) ⊕ X(i+2) ⊕ X(i+3) ⊕ RK(i)
                boxIn = xTemp[1] ^ xTemp[2] ^ xTemp[3] ^ RK[i];
                boxOut = sBox(boxIn);
                //X(i+4) = X(i) ⊕  sBox_output ⊕ Y2 ⊕ Y10 ⊕ Y18 ⊕ Y24
                int temp = xTemp[0] ^ boxOut ^ lShift(boxOut, 2) ^ lShift(boxOut, 10) ^ lShift(boxOut, 18) ^ lShift(boxOut, 24);
                xTemp[0] = xTemp[1];
                xTemp[1] = xTemp[2];
                xTemp[2] = xTemp[3];
                xTemp[3] = temp;
            }
        }else {
            for (int i = 31; i >= 0; i--) {
                boxIn = xTemp[1] ^ xTemp[2] ^ xTemp[3] ^ RK[i];
                boxOut = sBox(boxIn);
                int temp = xTemp[0] ^ boxOut ^ lShift(boxOut, 2) ^ lShift(boxOut, 10) ^ lShift(boxOut, 18) ^ lShift(boxOut, 24);
                xTemp[0] = xTemp[1];
                xTemp[1] = xTemp[2];
                xTemp[2] = xTemp[3];
                xTemp[3] = temp;
            }
        }

        byte[] des = new byte[16];
        //将最后 的 4 int  逆序 并转换为 byte
        for (int i = 0; i < 4; i++) {
            //每 32bit int 转换为 4 个 byte
            System.arraycopy(splitInt(xTemp[3 - i]), 0, des, 4 * i, 4);
        }
        return des;
    }


    /**
     * 转16进制字符串
     * @param ori 源
     * @return des
     */
    private static String bytesToHexString(byte[] ori) {
        StringBuilder des = new StringBuilder();
        //字符转换两位16进制字符
        for (byte b : ori) {
            des.append(String.format("%02X", b));
        }
        return "0X" + des;
    }

    /**
     * 16进制字符串转换byte[]
     * @param ori 源
     * @return bytes
     */
    private static byte[] hexStringToBytes(String ori) {
        StringBuilder str = new StringBuilder(ori.substring(2));
        int length = ori.length() - 2;
        if(length > 32){
            System.out.println("传入 明文/秘钥 输入不符要求 !");
            System.exit(0);
        }else {
            //填充 0
            str.append("0".repeat(Math.max(0, 32 - length)));
        }
        byte[] des = new byte[16];
        //每两位合并
        for (int i = 0; i < des.length; i++) {
            des[i] = (byte) Integer.parseInt(str.substring(i * 2, i * 2 + 2), 16);
        }
        return des;
    }

    /**
     * 子密钥 生成器
     * @param key 密钥
     */
    private static void generateKeys(byte[]  key) {
        //初始密钥 与 临时存储的四个运算密钥
        int[] keyTemp = new int[4];
        //S 盒变换输入和输出
        int boxIn, boxOut;

        /*
        // k = K ⊕ FK
        // 用 128bit 原密钥 生成 4个 初始密钥
         */
        for (int i = 0; i < 4; i++) {
            //将 4个 8位byte类型 转换为 32位int类型
            keyTemp[i] = byte4ToBit32(key[4 * i], key[4 * i + 1], key[4 * i + 2], key[4 * i + 3]);
            //与 FK 异或
            keyTemp[i] ^= FK[i];
        }

        /*
        // RK(i) = K(i) + 4 = K(i) ⊕ T′( K(i+1) ⊕ K(i+2) ⊕ K(i+3) ⊕ CK(i) )
        // T′(⋅) = L′( τ(⋅) )
        // τ(⋅) = sBox(K(i+1) ⊕ K(i+2) ⊕ K(i+3) ⊕ CK(i))
        // L′(B) = B ⊕ (B <<< 13) ⊕ (B <<< 23)
         */
        //32轮密钥拓展
        for (int i = 0; i < 32; i++) {
            // sBox_input = K(i+1) ⊕ K(i+2) ⊕ k(i+3) ⊕ CK(i)
            boxIn = keyTemp[1] ^ keyTemp[2] ^ keyTemp[3] ^ CK[i];
            // S 盒变换
            boxOut = sBox(boxIn);
            //密钥生成
            RK[i] = keyTemp[0] ^ boxOut ^ lShift(boxOut, 13) ^ lShift(boxOut, 23);
            // 重新对 临时密钥 赋值
            keyTemp[0] = keyTemp[1];
            keyTemp[1] = keyTemp[2];
            keyTemp[2] = keyTemp[3];
            keyTemp[3] = RK[i];
        }

    }

    /**
     * S 盒变换
     * @param boxInput 访问位置
     * @return 变换值
     */
    private static int sBox(int boxInput) {
        //将传递进来的 32bit 拆分 8bit
        byte[] temp = splitInt(boxInput);
        byte[] des = new byte[4];
        //S 盒变换
        for (int i = 0; i < 4; i++) {
            des[i] = (byte) S_BOX[temp[i] & 0xFF];
        }
        //将4个 8bit 合并为一个 32bit int 作为盒变换输出
        return byte4ToBit32(des[0], des[1], des[2], des[3]);
    }

    /**
     * int转换：int => 4byte
     * @param n 转换值
     * @return 4 x 8bit byte
     */
    private static byte[] splitInt(int n) {
        //拆分4分，分别返回
        return new byte[]{(byte) (n >>> 24), (byte) (n >>> 16),
                (byte) (n >>> 8), (byte) n};
    }

    /**
     * 循环左移
     * @param ori 左移目标
     * @param n 左移量
     * @return  左移数据
     */
    private static int lShift(int ori, int n) {
        //前n位 无符号右移 至最低位
        //后32-n位 左移至高位
        //两者 或运算
        return (ori >>> (32 - n)) | (ori << n);
    }

    /**
     * byte转换：4byte => int
     * @param b1 byte1
     * @param b2 byte2
     * @param b3 byte3
     * @param b4 byte4
     * @return int
     */
    private static int byte4ToBit32(byte b1, byte b2, byte b3, byte b4){
        //逐位 按高低 排列
        return ((b1 & 0xFF) << 24) | ((b2 & 0xFF) << 16) | ((b3 & 0xFF) << 8) | (b4 & 0xFF);
    }

    /**
     * 加密
     * @param plaintext 明文
     * @param key 密钥
     * @return 密文
     */
    public static byte[] encrypt(byte[] plaintext, byte[] key) {
        generateKeys(key);
        return cryptMainFunc(plaintext, 1);
    }

    /**
     * 解密
     * @param ciphertext 密文
     * @param key 密钥
     * @return 明文
     */
    public static byte[] decrypt(byte[] ciphertext, byte[] key) {
        //解密也调用密钥生成，为方便外部直接调用
        generateKeys(key);
        return cryptMainFunc(ciphertext,  0);
    }

    /**
     * 供外部测试
     */
    public static void test() {
        Scanner sc = new Scanner(System.in);
        System.out.println("输入要求:  长度不过32(不算0x)的以0x开头的16进制字符串\n");

        System.out.print("请输入明文: ");
        String p = sc.next();

        len = p.length();
        byte[] plaintext = hexStringToBytes(p);

        System.out.print("请输入密钥: ");
        byte[] key = hexStringToBytes(sc.next());
        //换行
        System.out.println();
        //加密
        byte[] cipher = encrypt(plaintext, key);
        System.out.println("加密结果: " + bytesToHexString(cipher));
        //解密
        byte[] decryptText = decrypt(cipher, key);
        System.out.println("解密结果: " + bytesToHexString(decryptText).substring(0, len));
    }

    public static void main(String[] args) {
        test();
    }
}
