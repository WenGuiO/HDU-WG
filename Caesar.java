package cryptograghy;

//import javafx.application.Application;
//import javafx.geometry.Insets;
//import javafx.scene.Scene;
//import javafx.scene.control.Button;
//import javafx.scene.control.Label;
//import javafx.scene.control.TextField;
//import javafx.scene.layout.VBox;
//import javafx.stage.Stage;

//启动图形界面需要 JDK1.8 或 手动导包

/**
 * 凯撒密码
 * @author wengui
 */
public class Caesar{
//public class Caesar extends Application {

/*
    @Override
    public void start(Stage primaryStage) {
        //创建标题
        primaryStage.setTitle("凯撒密码");

        //创建输入框，对应下边 lable标签
        TextField text = new TextField();
        TextField offsetFiled = new TextField();
        TextField encipherField = new TextField();
        TextField decryptField = new TextField();

        //创建三个说明标签
        Label textLabel = new Label("请输入明文/密文：");
        Label offsetLabel = new Label("请输入偏移量：");
        Label encipherLabel = new Label("加密后：");
        Label decryptLabel = new Label("原密文：");

        //操作按钮
        Button button = new Button("加/解密");

        button.setOnAction(e -> {
            int offset = Integer.parseInt(offsetFiled.getText());

            String plainText = caesarText(text.getText(), offset);
            String cipherText = caesarText(plainText, -offset);

            encipherField.setText(plainText);
            decryptField.setText(cipherText);
        });


        //创建垂直布局容器，添加标签，输入框和水平布局容器
        VBox vbox = new VBox(10);
        vbox.setPadding(new Insets(10));
        vbox.getChildren().addAll(textLabel, text, offsetLabel, offsetFiled, button,encipherLabel, encipherField
        ,decryptLabel, decryptField);

        // 创建场景，将布局容器添加到场景中
        Scene scene = new Scene(vbox, 300, 280);

        // 将场景添加到主舞台，并显示主舞台
        primaryStage.setScene(scene);
        primaryStage.show();
    }
*/

    /**
     * 凯撒加/解密
     * @param orgin 明文
     * @param offset 偏移量
     * @return 密文
     */
    public static String  caesarText(String orgin, int offset){
        StringBuffer  caesarStr = new StringBuffer();
        for (int i = 0; i < orgin.length(); i++) {
            char c = (char)('a' + (orgin.charAt(i) - 'a' + offset + 26) % 26);
            caesarStr.append(c);
        }
        return caesarStr.toString();
    }

    /**
     * 凯撒解密
     * @param ciphertext 密文
     * @param offset 偏移量
     * @return 明文
     */
    public static String decrypt(String ciphertext, int offset){
        StringBuffer  plaintext = new StringBuffer();
        for (int i = 0; i < ciphertext.length(); i++) {
            char c = (char)('a' + (ciphertext.charAt(i) - offset - 'a' + 26) % 26);
            plaintext.append(c);
        }
        return plaintext.toString();
    }

/*
    /**
     * 启动入口
     * @param args
     * /
    public static void main(String[] args) {
        launch(args);
    }
*/
}
