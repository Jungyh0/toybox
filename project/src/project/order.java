package project;

import java.awt.Component;
import java.awt.FlowLayout;
import java.awt.Image;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.KeyEvent;
import java.awt.event.KeyListener;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;

import javax.swing.*;
import javax.swing.event.MenuDragMouseEvent;
import javax.swing.event.MenuDragMouseListener;
import javax.swing.table.DefaultTableModel;
import javax.swing.table.TableCellRenderer;
import javax.swing.table.TableColumnModel;

public class order extends JFrame implements ActionListener,KeyListener{
	int index = kiosk.index;
	String[][] language = 
		{{"버거", "사이드", "음료", "커스텀"},
		{"burger","snack","drink", "Customized"},
		{"ハンバーガー", "おやつ", "飲み物", "カスタマイズされた"}, 
		{"汉堡包", "小吃","喝", "定制"}};
	JLabel text_output;
	JTabbedPane pane;
	JPanel pane1, top_pane;
	JButton cart_button;
	burger b = new burger();
	snack s = new snack();
	drink d = new drink();
	Customized c = new Customized();
	DB db = new DB();
	
	order(){
		super("주문");
		setSize(600,700);
	    setLocationRelativeTo(null);
	    setVisible(true);
	    setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
	    setResizable(false);
	    pane1 = new JPanel();
	    pane = new JTabbedPane();
	    String text = db.text[index][1];
	    top_pane = new JPanel();	add(top_pane,"North");
	    cart_button = new JButton(text);	top_pane.add(cart_button);
	    add(pane,"Center");
	    for(int i = 0; i < 4; i++) {
	    	if (i == 0)
	    		pane.addTab(language[index][i],b);
	    	else if (i == 1)
	    		pane.addTab(language[index][i], s);
	    	else if (i == 2)
	    		pane.addTab(language[index][i], d);
	    	else if (i == 3)
	    		pane.addTab(language[index][i], c);
	    }
	    cart_button.addActionListener(this);
	}

	@Override
	public void keyTyped(KeyEvent e) {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void keyPressed(KeyEvent e) {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void keyReleased(KeyEvent e) {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void actionPerformed(ActionEvent e) {
		// TODO Auto-generated method stub
		if(e.getSource() == cart_button)
			new cart();
		
	}
}

class burger extends JPanel implements MouseListener {
    String[] name_list = new String[3];
    int[] price_list = new int[3];
    String[] text_list = new String[1];
    String[] kacl_list = new String[3];
    int num = kiosk.index;
    DB dbc = new DB();
    JTable table;
    DefaultTableModel model;
    JScrollPane scroll;
    String[] columnNames = new String[] { "사진", "이름", "가격", "영양 정보" };
    User user = main.user;
    
    public burger() {
        Icon cs_burger = new ImageIcon("./image/cs_bu.png");
        Icon ch_burger = new ImageIcon("./image/ch_bu.png");
        Icon db_burger = new ImageIcon("./image/db_bu.png");

        dbc.select_burger(name_list, num);
        dbc.select_price(0, price_list);
        dbc.select_text(num, text_list, 0 ,1);
        dbc.select_kcal(kacl_list, 0);
        Object[][] rowData = new Object[][] {
            { cs_burger, name_list[0], price_list[0], kacl_list[0] },
            { ch_burger, name_list[1], price_list[1], kacl_list[1] },
            { db_burger, name_list[2], price_list[2], kacl_list[2] }
        };

        model = new DefaultTableModel(rowData, columnNames) {
            @Override
            public boolean isCellEditable(int row, int column) {
                return false;
            }

            @Override
            public Class<?> getColumnClass(int column) {
                if (column == 0) {
                    return Icon.class;
                }
                return Object.class;
            }
        };

        table = new JTable(model);
        table.setRowHeight(100);
        resizeColumnWidth(table);
        table.addMouseListener(this);
        scroll = new JScrollPane(table);
        add(scroll);
    }

    public void resizeColumnWidth(JTable table) {
        final TableColumnModel columnModel = table.getColumnModel();
        for (int column = 0; column < table.getColumnCount(); column++) {
            int width = 50;
            for (int row = 0; row < table.getRowCount(); row++) {
                TableCellRenderer renderer = table.getCellRenderer(row, column);
                Component comp = table.prepareRenderer(renderer, row, column);
                width = Math.max(comp.getPreferredSize().width + 1, width);
            }
            columnModel.getColumn(column).setPreferredWidth(width);
        }
    }

    @Override
    public void mousePressed(MouseEvent e) {
        JTable t = (JTable) e.getSource();
        if (e.getClickCount() == 2) {
            int row1 = table.getSelectedRow();
            int col = table.getSelectedColumn();
            String name = (String) table.getValueAt(row1, 1);
            int price = (int) table.getValueAt(row1, 2);
            System.out.print(name + "\t");
            int result = JOptionPane.showConfirmDialog(this, "'" + name + "'" + text_list[0], "Confirm", JOptionPane.YES_NO_OPTION);
            if (result == JOptionPane.YES_OPTION) {
                System.out.println(name + ", " + price + "이 추가 되었습니다!");
                user.input_cart(user, name, price);
                user.total_price += price;
                System.out.println("총 가격: " + user.total_price);
            }
        }
    }

    @Override
    public void mouseClicked(MouseEvent e) {}

    @Override
    public void mouseReleased(MouseEvent e) {}

    @Override
    public void mouseEntered(MouseEvent e) {}

    @Override
    public void mouseExited(MouseEvent e) {}
}


class snack extends JPanel implements MouseListener{
    String[] name_list = new String[3];
    int[] price_list = new int[3];
    String[] kacl_list = new String[3];
    int num = kiosk.index;
    DB dbc = new DB();
    String[] text_list = new String[1];
    JTable table;
    DefaultTableModel model;
    JScrollPane scroll;
    String[] columnNames = new String[] { "사진", "이름", "가격", "영양 정보" };
    User user = main.user;

    public snack() {
        Icon cs_burger = new ImageIcon("./image/fri.png");
        Icon ch_burger = new ImageIcon("./image/ch_nu.png");
        Icon db_burger = new ImageIcon("./image/sti.png");

        dbc.select_snack(name_list, num);
        dbc.select_price(1, price_list);
        dbc.select_text(num, text_list, 0, 1);
        dbc.select_kcal(kacl_list, 1);
        Object[][] rowData = new Object[][] {
            { cs_burger, name_list[0], price_list[0] ,kacl_list[0]},
            { ch_burger, name_list[1], price_list[1] ,kacl_list[1]},
            { db_burger, name_list[2], price_list[2] ,kacl_list[2]}
        };

        model = new DefaultTableModel(rowData, columnNames) {
            @Override
            public boolean isCellEditable(int row, int column) {
                return false;
            }

            @Override
            public Class<?> getColumnClass(int column) {
                if (column == 0) {
                    return Icon.class;
                }
                return Object.class;
            }
        };
        
        table = new JTable(model);
        table.setRowHeight(100); // 이미지가 잘 보이도록 행 높이 조절
        resizeColumnWidth(table);
        scroll = new JScrollPane(table);
        table.addMouseListener(this);
        add(scroll);
    }

    public void resizeColumnWidth(JTable table) {
        final TableColumnModel columnModel = table.getColumnModel();
        for (int column = 0; column < table.getColumnCount(); column++) {
            int width = 50;
            for (int row = 0; row < table.getRowCount(); row++) {
                TableCellRenderer renderer = table.getCellRenderer(row, column);
                Component comp = table.prepareRenderer(renderer, row, column);
                width = Math.max(comp.getPreferredSize().width + 1, width);
            }
            columnModel.getColumn(column).setPreferredWidth(width);
        }
    }
    
    @Override
    public void mousePressed(MouseEvent e) {
        JTable t = (JTable) e.getSource();
        if (e.getClickCount() == 2) {
            int row1 = table.getSelectedRow();
            int col = table.getSelectedColumn();
            String name = (String) table.getValueAt(row1, 1);
            int price = (int) table.getValueAt(row1, 2);
            System.out.print(name + "\t");
            int result = JOptionPane.showConfirmDialog(this, "'" + name + "'" + text_list[0], "Confirm", JOptionPane.YES_NO_OPTION);
            if (result == JOptionPane.YES_OPTION) {
                System.out.println(name + "이 추가 되었습니다!");
                user.input_cart(user, name, price);
                user.total_price += price;
            }
        }
    }
    @Override
    public void mouseClicked(MouseEvent e) {}

    @Override
    public void mouseReleased(MouseEvent e) {}

    @Override
    public void mouseEntered(MouseEvent e) {}

    @Override
    public void mouseExited(MouseEvent e) {}
}

class drink extends JPanel implements MouseListener{
    String[] name_list = new String[3];
    int[] price_list = new int[3];
    int num = kiosk.index;
    String[] text_list = new String[1];
    String[] kacl_list = new String[3];
    DB dbc = new DB();
    JTable table;
    DefaultTableModel model;
    JScrollPane scroll;
    String[] columnNames = new String[] { "사진", "이름", "가격", "영양 정보" };
    User user = main.user;

    public drink() {

        Icon cs_burger = new ImageIcon("./image/co.png");
        Icon ch_burger = new ImageIcon("./image/ci.png");
        Icon db_burger = new ImageIcon("./image/fan.png");

        dbc.select_drink(name_list, num);
        dbc.select_price(2, price_list);
        dbc.select_text(num, text_list, 0, 1);
        dbc.select_kcal(kacl_list, 2);
        Object[][] rowData = new Object[][] {
            { cs_burger, name_list[0], price_list[0],kacl_list[0] },
            { ch_burger, name_list[1], price_list[1],kacl_list[1] },
            { db_burger, name_list[2], price_list[2], kacl_list[2]}
        };

        model = new DefaultTableModel(rowData, columnNames) {
            @Override
            public boolean isCellEditable(int row, int column) {
                return false;
            }

            @Override
            public Class<?> getColumnClass(int column) {
                if (column == 0) {
                    return Icon.class;
                }
                return Object.class;
            }
        };
        
        table = new JTable(model);
        table.setRowHeight(100); // 이미지가 잘 보이도록 행 높이 조절
        resizeColumnWidth(table);
        scroll = new JScrollPane(table);
        table.addMouseListener(this);
        add(scroll);
    }

    public void resizeColumnWidth(JTable table) {
        final TableColumnModel columnModel = table.getColumnModel();
        for (int column = 0; column < table.getColumnCount(); column++) {
            int width = 50;
            for (int row = 0; row < table.getRowCount(); row++) {
                TableCellRenderer renderer = table.getCellRenderer(row, column);
                Component comp = table.prepareRenderer(renderer, row, column);
                width = Math.max(comp.getPreferredSize().width + 1, width);
            }
            columnModel.getColumn(column).setPreferredWidth(width);
        }
    }
    @Override
    public void mousePressed(MouseEvent e) {
        JTable t = (JTable) e.getSource();
        if (e.getClickCount() == 2) {
            int row1 = table.getSelectedRow();
            int col = table.getSelectedColumn();
            String name = (String) table.getValueAt(row1, 1);
            int price = (int) table.getValueAt(row1, 2);
            System.out.print(name + "\t");
            int result = JOptionPane.showConfirmDialog(this, "'" + name + "'" + text_list[0], "Confirm", JOptionPane.YES_NO_OPTION);
            if (result == JOptionPane.YES_OPTION) {
                System.out.println(name + "이 추가 되었습니다!");
                user.input_cart(user, name, price);
                user.total_price += price;
            }
        }
    }
    @Override
    public void mouseClicked(MouseEvent e) {}

    @Override
    public void mouseReleased(MouseEvent e) {}

    @Override
    public void mouseEntered(MouseEvent e) {}

    @Override
    public void mouseExited(MouseEvent e) {}
}

class Customized extends JPanel implements ActionListener {
    JButton addOnionButton, removeOnionButton;
    JButton addTomatoButton, removeTomatoButton;
    JButton addKetchupButton, removeKetchupButton;
    JButton addMustardButton, removeMustardButton;
    JButton addCheeseButton, removeCheeseButton;
    JLabel text;
    String[] cust_list;
    String[] qu_list;
    public String[][] text_list = {
            // 한국어
            {"개당 500원 추가"},
            // 영어
            {"Additional 500 won each"},
            // 일본어
            {"それぞれ500ウォン追加"},
            // 중국어
            {"每个加500韩元"}
        };
    DB d = new DB();
    int index = kiosk.index;

    public Customized() {
        // Layout 설정
        setLayout(new BoxLayout(this, BoxLayout.Y_AXIS));
        cust_list = new String[10];
        d.select_cust_menu(cust_list, index);
        text = new JLabel(text_list[index][0]);	add(text);
        
        // 야채 추가/제거 옵션
        addOnionButton = new JButton(cust_list[0]);
        removeOnionButton = new JButton(cust_list[1]);
        addTomatoButton = new JButton(cust_list[2]);
        removeTomatoButton = new JButton(cust_list[3]);

        addOnionButton.addActionListener(this);
        removeOnionButton.addActionListener(this);
        addTomatoButton.addActionListener(this);
        removeTomatoButton.addActionListener(this);

        // 소스 선택 옵션
        addKetchupButton = new JButton(cust_list[4]);
        removeKetchupButton = new JButton(cust_list[5]);
        addMustardButton = new JButton(cust_list[6]);
        removeMustardButton = new JButton(cust_list[7]);

        addKetchupButton.addActionListener(this);
        removeKetchupButton.addActionListener(this);
        addMustardButton.addActionListener(this);
        removeMustardButton.addActionListener(this);

        // 치즈 추가/제거 옵션
        addCheeseButton = new JButton(cust_list[8]);
        removeCheeseButton = new JButton(cust_list[9]);

        addCheeseButton.addActionListener(this);
        removeCheeseButton.addActionListener(this);

        // 버튼들을 패널에 원하는 순서로 추가
        add(addOnionButton);
        add(removeOnionButton);
        add(addTomatoButton);
        add(removeTomatoButton);
        add(addKetchupButton);
        add(removeKetchupButton);
        add(addMustardButton);
        add(removeMustardButton);
        add(addCheeseButton);
        add(removeCheeseButton);
    }




    @Override
    public void actionPerformed(ActionEvent e) {
    	qu_list = new String[12];
    	d.select_text(index, qu_list, 2, 10);
        if (e.getSource() == addOnionButton) {
            JOptionPane.showMessageDialog(this, qu_list[2]);	User.total_price += 500;
            // TODO: 사용자의 선택을 반영하여 로직 추가
        } else if (e.getSource() == removeOnionButton) {
            JOptionPane.showMessageDialog(this, qu_list[3]);
            // TODO: 사용자의 선택을 반영하여 로직 추가
        } else if (e.getSource() == addTomatoButton) {
            JOptionPane.showMessageDialog(this, qu_list[4]);	User.total_price += 500;
            // TODO: 사용자의 선택을 반영하여 로직 추가
        } else if (e.getSource() == removeTomatoButton) {
            JOptionPane.showMessageDialog(this, qu_list[5]);
            // TODO: 사용자의 선택을 반영하여 로직 추가
        } else if (e.getSource() == addKetchupButton) {
            JOptionPane.showMessageDialog(this, qu_list[6]);	User.total_price += 500;
            // TODO: 사용자의 선택을 반영하여 로직 추가
        } else if (e.getSource() == removeKetchupButton) {
            JOptionPane.showMessageDialog(this, qu_list[7]);
            // TODO: 사용자의 선택을 반영하여 로직 추가
        } else if (e.getSource() == addMustardButton) {
            JOptionPane.showMessageDialog(this, qu_list[8]);	User.total_price += 500;
            // TODO: 사용자의 선택을 반영하여 로직 추가
        } else if (e.getSource() == removeMustardButton) {
            JOptionPane.showMessageDialog(this, qu_list[9]);
            // TODO: 사용자의 선택을 반영하여 로직 추가
        } else if (e.getSource() == addCheeseButton) {
            JOptionPane.showMessageDialog(this, qu_list[10]);	User.total_price += 500;
            // TODO: 사용자의 선택을 반영하여 로직 추가
        } else if (e.getSource() == removeCheeseButton) {
            JOptionPane.showMessageDialog(this, qu_list[11]);
            // TODO: 사용자의 선택을 반영하여 로직 추가
        }
    }
}