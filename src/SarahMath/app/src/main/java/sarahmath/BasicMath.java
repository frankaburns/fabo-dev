package sarahmath;
public class BasicMath {

  public final static int ADD = 0;
  public final static int SUB = 1;
  public final static int MUL = 2;
  public final static int DIV = 3;

  private      int Function;
  private      int Numerator;
  private      int Denominator;

  BasicMath (int func) {
    Numerator     =
    Denominator   = 0;
    Function = func;
  }

  public int doTheMath (int func) {

    int Result;

    switch (func) {
      case ADD:
        Result = Numerator + Denominator;
        break;

      case SUB:
        Result = Numerator - Denominator;
        break;

      case MUL:
        Result = Numerator * Denominator;
        break;

      case DIV:
        Result = Numerator / Denominator;
        break;

      default:
        Result = -1;
        break;
    }

    return Result;
  }

  public void setNumerator ( int t) {
    Numerator = t;
  }

  public void setDenominator ( int b) {
    Denominator = b;
  }

  public void setFunction (int f) {
    Function = f;
  }

  public int getNumerator () {
    return (Numerator);
  }

  public int getDenominator () {
    return (Denominator);
  }

  public int getFunction () {
    return (Function);
  }

  public int getNumeratorWidth () {
    int width = 1;
    int more  = Numerator;

    while ((more=more/10) > 0) width++;
    return (width);
  }

  public int getDenominatorWidth () {
    int width = 1;
    int more  = Denominator;

    while ((more=more/10) > 0) width++;
    return (width);
  }

};
