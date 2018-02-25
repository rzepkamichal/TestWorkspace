package application;


public class Coefficients implements ISetCoefficients  {
	//bellow there are all needed variables
	private double[] coeffA,coeffB,coeffC,coeffD,beta,gamma,solutions;//tabs containing the values of coefficients and beta/gamma tabs which contain the values of variables needed in calculating
	private int numberOfEquations;
	
	public Coefficients(int numberOfEquations){//Constructor method which sets the number of equations and creates tables containing all coefficients
		this.numberOfEquations=numberOfEquations;
		coeffA=new double[this.numberOfEquations];
			coeffA[0]=0.0;
		coeffB=new double[this.numberOfEquations];
		coeffC=new double[this.numberOfEquations];
			coeffC[numberOfEquations-1]=0.0;
		coeffD=new double[this.numberOfEquations];
		beta=new double[this.numberOfEquations];
		gamma=new double[this.numberOfEquations];
		solutions=new double[this.numberOfEquations];
	}
	@Override
	public void setCoeffa(int i, double arg) {
		coeffA[i]=arg;
	}
	@Override
	public void setCoeffb(int i,double arg) {
		coeffB[i]=arg;	
	}
	@Override
	public void setCoeffc(int i,double arg) {
		coeffC[i]=arg;
	}
	@Override
	public void setCoeffd(int i, double arg) {
		coeffD[i]=arg;
	}
	@Override
	public double getCoeffa(int i) {	
		return coeffA[i];
	}
	@Override
	public double getCoeffb(int i) {		
		return coeffB[i];
	}
	@Override
	public double getCoeffc(int i) {
		return coeffC[i];
	}
	@Override
	public double getCoeffd(int i) {	
		return coeffD[i];
	}
	@Override
	public double getBeta(int i) {
		return beta[i];
	}
	@Override
	public double getGamma(int i) {	
		return gamma[i];
	}	
	@Override
	public double getSolution(int i) {
		return solutions[i];
	}
	public void CalculateBetaGamma(){
		beta[0]=(-(getCoeffc(0))/(getCoeffb(0)));
		gamma[0]=((getCoeffd(0))/(getCoeffb(0)));
		
		for(int i=1;i<numberOfEquations;i++){
			if(i<numberOfEquations-1){
				beta[i]=(-(getCoeffc(i))/((getCoeffa(i)*getBeta(i-1))+getCoeffb(i)));
			}
			gamma[i]=((getCoeffd(i)-(getCoeffa(i)*getGamma(i-1)))/((getCoeffa(i)*getBeta(i-1))+getCoeffb(i)));
		}
	}
	public void CalculateSolution(){
		
		solutions[numberOfEquations-1]=getGamma(numberOfEquations-1);
		for(int i=numberOfEquations-2;i>=0;i--){
			solutions[i]=(getBeta(i)*getSolution(i+1))+getGamma(i);
		}
	}
	public double ExportSolution(int i){
		return getSolution(i);
	}

}
