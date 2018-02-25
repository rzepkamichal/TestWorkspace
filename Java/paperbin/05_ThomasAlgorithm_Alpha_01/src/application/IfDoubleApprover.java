package application;

public class IfDoubleApprover {
	
	private static double testVariable;
	
	public static void check(double arg){//first static method which is  used to trigger the appearing of an error in order to catch it
		testVariable=arg;
	}

}
