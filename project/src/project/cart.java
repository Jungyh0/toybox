
package project;

import java.awt.FlowLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import javax.swing.*;

public class cart extends JFrame {
    User user = main.user;
    JLabel[] name, price;
    JButton[] cancel_button;
    String[] name_list = user.order_list;
    int[] price_list = user.price;
    int index = user.index;
    JPanel cart_pane, price_pane;
    JLabel price_label;
    String total;
    JButton payment_button;

    cart() {
        super("Cart");
        setSize(500, 400);
        setLocationRelativeTo(null);
        setResizable(false);

        if (user.total_price <= 0) {
            total = "장바구니가 비어있습니다.";
        } else {
            total = user.total_price + "원";
        }

        cart_pane = new JPanel();
        price_pane = new JPanel();
        
        name = new JLabel[index];
        price = new JLabel[index];
        cancel_button = new JButton[index];
        price_label = new JLabel("총 가격: " + total);
        payment_button = new JButton("결제");
        
        price_pane.add(payment_button);
        price_pane.add(price_label);

        for (int i = 0; i < index; i++) {
            String pr = price_list[i] + "원";
            name[i] = new JLabel(name_list[i]);
            price[i] = new JLabel(pr);
            cancel_button[i] = new JButton("취소");

            cart_pane.add(name[i]);
            cart_pane.add(price[i]);
            cart_pane.add(cancel_button[i]);
   
        }

        add(cart_pane, "Center");
        add(price_pane, "South");
        
        payment_button.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                showPaymentDialog();
            }
        });

        setVisible(true);
    }

    private void showPaymentDialog() {
        int response = JOptionPane.showConfirmDialog(this, "결제하시겠습니까?", "결제 확인", JOptionPane.YES_NO_OPTION);
        if (response == JOptionPane.YES_OPTION) {
            JOptionPane.showMessageDialog(this, "결제되었습니다.");
            user.total_price = 0;
            setVisible(false);
        } else {
            JOptionPane.showMessageDialog(this, "결제취소되었습니다.");
        }
    }
}




