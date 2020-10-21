/*************************************************************************
  Created Time: 2020-04-13 16:17:37
 ************************************************************************/
public class Main
{
	native private int intMethod(int i, int j);
	native public static String stringMethod(String str, int i);
	public static void main(String[] args)
	{
		static{
			System.loadLibrary("main");// 只加载一次
		}
		
		System.out.println("hello world!");
	}
}
