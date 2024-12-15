package project;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;

public class DB_connecter {

	public static void main(String[] args) {
	       Connection conn = null;
	        try {
	            // SQLite JDBC 드라이버 로드
	            Class.forName("org.sqlite.JDBC");

	            // 데이터베이스에 연결
	            String url = "jdbc:sqlite:sample.db";
	            conn = DriverManager.getConnection(url);

	            System.out.println("연결 성공!");

	        } catch (ClassNotFoundException e) {
	            System.out.println("JDBC 드라이버를 찾을 수 없습니다: " + e.getMessage());
	        } catch (SQLException e) {
	            System.out.println("데이터베이스 연결 실패: " + e.getMessage());
	        } finally {
	            try {
	                if (conn != null) {
	                    conn.close();
	                }
	            } catch (SQLException ex) {
	                System.out.println("연결 종료 실패: " + ex.getMessage());
	            }
	        }
    }
}
