package application;

public class NumberApprover {
	
	private static double testNumber;
	
	public static void checkout(double arg){
		if(arg<1)
		{
			throw new NumberFormatException();//second static method which is used to trigger the appearing of an error in order to catch it (negative number)
		} else {
			testNumber=arg;
		}
		
	}
}

