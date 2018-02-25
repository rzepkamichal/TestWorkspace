package thomas_algorithm;
import java.util.Scanner;
public class Program {
public static void main(String[] args) {
	
	Scanner console=new Scanner (System.in);
	
	
		System.out.println("Podaj iloœæ równañ: ");
	int n=console.nextInt();

	double[] a=new double[n];a[0]=0;
	double[] b=new double[n];
	double[] c=new double[n];c[n-1]=0;
	double[] d=new double[n];
	double[] beta=new double[n];
	double[] gamma=new double[n];
	double[] x=new double[n];
	
	for(int i=1;i<n;i++){
			System.out.println("Podaj wartoœæ wspó³czynnika a"+(i+1)+": ");
		a[i]=console.nextDouble();
	}
	for(int i=0;i<n;i++){
		System.out.println("Podaj wartoœæ wspó³czynnika b"+(i+1)+": ");
	b[i]=console.nextDouble();
	}
	for(int i=0;i<n-1;i++){
		System.out.println("Podaj wartoœæ wspó³czynnika c"+(i+1)+": ");
	c[i]=console.nextDouble();
	}
	for(int i=0;i<n;i++){
		System.out.println("Podaj wartoœæ wspó³czynnika d"+(i+1)+": ");
	d[i]=console.nextDouble();
	}
	
	beta[0]=-c[0]/b[0];
	gamma[0]=d[0]/b[0];

	for(int i=1;i<n;i++){
		beta[i]=(-c[i])/(a[i]*beta[i-1]+b[i]);
		gamma[i]=(d[i]-a[i]*gamma[i-1])/(a[i]*beta[i-1]+b[i]);
	}
	x[n-1]=gamma[n-1];
	
	for(int i=n-2;i>-1;i--)
		x[i]=beta[i]*x[i+1]+gamma[i];
	
	
	for(double i: x)
		System.out.println(i);
	}
}
