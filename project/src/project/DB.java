package project;

public class DB {
	public String[][] burger = 
			{{"치즈 버거", "치킨 버거", "더블 버거"},
			{"cheeseburger", "Chicken Sandwich", "double burger"}, 
			{"チーズバーガー", "チキンバーガー", "ダブルバーガー"},
			{"芝士汉堡", "鸡肉汉堡", "双汉堡"}};
	
	public String[][] snack = 
			{{"감자튀김", "치킨너겟", "치즈 스틱"},
			{"French fries", "Chicken Nuggets", "Cheese Sticks"}, 
			{"フライドポテト", "チキンナゲット", "チーズスティック"},
			{"炸薯条", "鸡块", "奶酪棒"}};

	
	public String[][] drink = 
			{{"콜라", "사이다", "환타"},
			{"Cork", "cider", "Fanta"}, 
			{"コーラ", "サイダ", "ファンタ"},
			{"可乐", "雪碧", "芬达"}};
	
	public String[][] kcal = {
			{"400kcal", "450kcal", "500kcal"},
			{"300kcal", "350kcal", "200kcal"},
			{"150kcal", "140kcal", "160kcal"}
	};
	
	public String[][] cust = {
	        // 한국어
	        {
	            "양파 추가", "양파 제거", "토마토 추가", "토마토 제거", "케첩 추가", "케첩 제거", "머스타드 추가", "머스타드 제거", "치즈 추가", "치즈 제거"
	        },
	        // 영어
	        {
	            "Add Onion", "Remove Onion", "Add Tomato", "Remove Tomato", "Add Ketchup", "Remove Ketchup", "Add Mustard", "Remove Mustard", "Add Cheese", "Remove Cheese"
	        },
	        // 일본어
	        {
	            "玉ねぎ追加", "玉ねぎ除去", "トマト追加", "トマト除去", "ケチャップ追加", "ケチャップ除去", "マスタード追加", "マスタード除去", "チーズ追加", "チーズ除去"
	        },
	        // 중국어
	        {
	            "加洋葱", "去洋葱", "加番茄", "去番茄", "加番茄酱", "去番茄酱", "加芥末", "去芥末", "加芝士", "去芝士"
	        }
	    };
	
	
	public int[][] price = {{5000, 7000, 10000},{3000, 4000, 2000},{2000, 2000, 2000}};
	
    public String[][] text = {
            // 한국어
            {
                "을(를) 추가하시겠습니까?", "장바구니", "양파가 추가되었습니다.", "양파가 제거되었습니다.", "토마토가 추가되었습니다.", "토마토가 제거되었습니다.", "케첩이 추가되었습니다.", "케첩이 제거되었습니다.", "머스타드가 추가되었습니다.", "머스타드가 제거되었습니다.", "치즈가 추가되었습니다.", "치즈가 제거되었습니다."
            },
            // 영어
            {
                "Would you like to add it?", "Cart", "Onion has been added.", "Onion has been removed.", "Tomato has been added.", "Tomato has been removed.", "Ketchup has been added.", "Ketchup has been removed.", "Mustard has been added.", "Mustard has been removed.", "Cheese has been added.", "Cheese has been removed."
            },
            // 일본어
            {
                "追加しますか？", "カート", "玉ねぎが追加されました。", "玉ねぎが除去されました。", "トマトが追加されました。", "トマトが除去されました。", "ケチャップが追加されました。", "ケチャップが除去されました。", "マスタードが追加されました。", "マスタードが除去されました。", "チーズが追加されました。", "チーズが除去されました。"
            },
            // 중국어
            {
                "您想添加吗？", "购物车", "洋葱已添加。", "洋葱已去除。", "番茄已添加。", "番茄已去除。", "番茄酱已添加。", "番茄酱已去除。", "芥末已添加。", "芥末已去除。", "芝士已添加。", "芝士已去除。"
            }
        };
	
	public void select_burger(String[] list, int x) {
		for(int i = 0; i < 3; i++) {
			list[i] = burger[x][i];
		}
	}
	
	public void select_cust_menu(String[] list, int x) {
		for(int i = 0; i < 10; i++) {
			list[i] = cust[x][i];
		}
	}
	
	public void select_kcal(String[] list, int x) {
		for(int i = 0; i < 3; i++) {
			list[i] = kcal[x][i];
		}
	}
	
	public void select_price(int x, int[] list) {
		for(int i = 0; i < 3; i++) {
			list[i] = price[x][i];
		}
	}
	
	public void select_text(int x, String[] list, int start, int end) {
		for(int i = start; i < end; i++) {
			list[i] = text[x][i];
		}
	}
	
	public void select_snack(String[] list, int x) {
		for(int i = 0; i < 3; i++) {
			list[i] = snack[x][i];
		}
	}

	
	public void select_drink(String[] list, int x) {
		for(int i = 0; i < 3; i++) {
			list[i] = drink[x][i];
		}
	}

	
}
