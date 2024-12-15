package project;

public class User {
	static int index;
	static String id, pw;
	static String[] order_list;
	static int total_price;
	static int[] price;
	
	User(){
		total_price = 0;
		index = 0;
		order_list = new String[10];
		price = new int[10];
	}
	static void input_cart(User user, String name, int price) {
		user.order_list[index] = name;
		user.price[index] = price;
	}
}
