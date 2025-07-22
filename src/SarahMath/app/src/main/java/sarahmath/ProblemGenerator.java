package sarahmath;
import java.io.FileWriter;
import java.io.PrintWriter;
import java.util.Properties;

public
class ProblemGenerator {

    public  static int     inp;

    public  static int     num;
    public  static int     mag;
    public  static int     res;

    public  static int     rows;
    public  static int     cols;

    public  static int     numWrong;
    public  static int     problemCount;
    public  static int     numProblems;
    public  static int     lessonFunction; // 0-ADD, 1-SUB, 2-MUL, 3-DIV

    public  static char    c;

    public static boolean printList;
    public static boolean randomProblem;

    /**
     * 
     */
    ProblemGenerator() {
      rows          = 10;
      cols          = 10;

      numWrong      = 0;
      problemCount  = 0;
      numProblems   = 25;
      
      printList     = false;
      randomProblem = false;  

      subSet        = new BasicMath[rows*cols];
      problemSet    = new BasicMath[rows*cols];

    }

    /**
     * 
     * @param rows
     * @param cols
     */
    ProblemGenerator(int rows, int cols) {  
      numWrong      = 0;
      problemCount  = 0;
      numProblems   = 25;
    
      printList     = false;
      randomProblem = false;  

      subSet        = new BasicMath[rows*cols];
      problemSet    = new BasicMath[rows*cols];

    }

    /**
     * 
     * @param n
     */
    public void setnumProblems ( int n) {
      numProblems = n;
    }

    /**
     * 
     * @param p
     */
    public void setrandomProblem ( boolean p) {
      randomProblem = p;
    }

    /**
     * 
     * @param f
     */
    public void setlessonFunction (int f) {
      lessonFunction = f;
    }

    /**
     * 
     * @return
     */
    public int getnumProblems () {
      return (numProblems);
    }

    /**
     * 
     * @return
     */
    public boolean getrandomProblem () {
      return (randomProblem);
    }

    /**
     * 
     * @return
     */
    public int getlessonFunction () {
      return (lessonFunction);
    }


    /**
     * Method to execute the mathmatical function described by the BasicMath 
     * object. The basic math has a function, a numerator and a denominator.
     * 
     * @param problem - a basic math object.
     * @throws Exception - exception (devide by zero maybe?)
     */
    public int doProblem(BasicMath problem) throws Exception {

      int  wrong       = 0;
      Properties p     = System.getProperties();
      String separator = p.getProperty("line.separator");
       
      do {

        System.out.print ("\n\n");
        System.out.print("      " + problem.getTop() + "\n");
        System.out.print("    ");

        switch (problem.getFunction()) {

          case BasicMath.ADD:
            System.out.print("+ ");
            break;

          case BasicMath.SUB:
            System.out.print("- ");
            break;

          case BasicMath.MUL:
            System.out.print("X ");
            break;

          case BasicMath.DIV:
            System.out.print("/ ");
            break;

          default:
            break;

        }

        System.out.print(problem.getBottom() + "\n");        
        System.out.print("    ____\n" + "      ");
        mag =
        res = problem.doTheMath(problem.getFunction());
        num = getAnswer(separator);

        if (res != num) {
          System.out.print("Wrong Answer SARAH!!!!!\n");
          wrong++;
        }
      } while (res != num);
      return wrong;
    }

    /**
     * 
     * @param problem
     * @param numElements
     * @throws Exception
     */
    public void doSarahStyle(BasicMath[] problem, int numElements) throws Exception {

      final PrintWriter writer = new PrintWriter(new FileWriter (new String("c:\\jdk1.3\\tmp\\lesson.txt")));

      for (int i=0; i<numElements; i+=6) {

        if (i%48 == 0 && i != 0) writer.print ("\f");

        writer.print ("\n\n\n\n");
        for (int j=0; j<6; j++) {                              
          if (i+j < numElements) { 
            for (int spaces=0; spaces<11-problem[i+j].getTopWidth(); spaces++) writer.print (" ");
            writer.print (problem[i+j].getTop());
          }
        }

        writer.print ("\n");

        for (int j=0; j<6; j++) {
          if (i+j >= numElements) break;
          for (int spaces=0; spaces<11-2-problem[i+j].getBottomWidth(); spaces++) writer.print (" ");
          if (i+j < numElements) {
            switch (problem[i+j].getFunction()) {
        
              case BasicMath.ADD:
                writer.print("+ ");
                break;

              case BasicMath.SUB:
                writer.print("- ");
                break;

              case BasicMath.MUL:
                writer.print("x ");
                break;

              case BasicMath.DIV:
                writer.print("/ ");
                break;

              default:
                break;

            }

            writer.print (problem[i+j].getBottom());
          }
        }

        writer.print ("\n");

        for (int j=0; j<6; j++) {
          if (i+j < numElements) writer.print("       ____");
        }

        writer.print ("\n");
      }
      writer.close();
    }
    
    /**
     * 
     */
    private void shuffleArray () {

      for( int prob = 0; prob < problemSet.length; prob++ ){
        int newPosition         = (int)(Math.random()*100)%(rows*cols);
        BasicMath tmp           = problemSet[newPosition];
        problemSet[newPosition] = problemSet[prob];
        problemSet[prob]        = tmp;
      }
    }

    /**
     * 
     * @param rows
     * @param cols
     */
    private void buildProblemSet (int rows, int cols) {
      problemCount = rows*cols;
      for( int i = 0, iPlusOne = 1; i < rows; i++, iPlusOne++ ){     
        for( int j = 0, jPlusOne = 1; j < cols; j++, jPlusOne++ ){
          int idx = i*(rows)+j;
          problemSet[idx] = new BasicMath(lessonFunction);
          problemSet[idx].setTop(iPlusOne);
          problemSet[idx].setBottom(jPlusOne);
        }
      }

      if (randomProblem) {
        shuffleArray ();
      }

      if (lessonFunction == BasicMath.SUB) {
        int iterations = rows*cols;
        for (int i=0; i<iterations; i++) {
          if (problemSet[i].getTop() >= problemSet[i].getBottom()) { 
            subSet[problemCount] = new BasicMath(problemSet[i].getFunction());
            subSet[problemCount].setTop(problemSet[i].getTop());
            subSet[problemCount++].setBottom(problemSet[i].getBottom());
         }
        }     
      }

      if (lessonFunction == BasicMath.DIV) {
        int iterations = rows*cols;
        for (int i=0; i<iterations; i++) {
          if ( (problemSet[i].getTop() >= problemSet[i].getBottom()) && 
               ((problemSet[i].getTop()%problemSet[i].getBottom()) == 0) ) { 
            subSet[problemCount] = new BasicMath(problemSet[i].getFunction());
            subSet[problemCount].setTop(problemSet[i].getTop());
            subSet[problemCount++].setBottom(problemSet[i].getBottom());
         }
        }     
      }
    }

    /**
     * 
     * @param sepString
     * @return
     * @throws Exception
     */
    public int getAnswer(String sepString) throws Exception {

      int ans   = 0;
      int start = 0;

      do {
        c = (char)(inp = System.in.read());

        if (Character.isDigit(c)) {
          ans = ans*10 +  Character.digit(c,10);
        } else if (Character.getType(c) == Character.CONTROL) {
          start += 1;
          break;
        } else if (c == 'e') {
          System.exit(0);
        }
      } while (true);

      for( int k = start; k < sepString.length(); k++ ) {
        inp = System.in.read();
      }

      return ans;
    }

    /**
     * 
     * @throws Exception
     */

    public void problemSet() throws Exception {

      buildProblemSet(rows, cols);

      System.out.println("random: " + randomProblem);
      System.out.println("function: " + lessonFunction);
      System.out.println("problems: " + numProblems);
    /**
       * Do the problems
       */
      numProblems = (numProblems < problemCount) ? numProblems : problemCount;

      if (printList) {
        if (lessonFunction == BasicMath.SUB) {
          doSarahStyle (subSet,numProblems);
        } else {
          doSarahStyle (problemSet,numProblems);
        }

      } else {

        for (int i=0; i<numProblems; i++) {
          if (lessonFunction == BasicMath.SUB  || lessonFunction == BasicMath.DIV) {
            numWrong += (doProblem (subSet[i]) > 0) ? 1 : 0;
          } else {
            numWrong += doProblem (problemSet[i]);
          }
        }
        double nw = numWrong;
        double nl = numProblems;
        double score = ((nl-nw)/nl)*100.0; 
        System.out.print("\n\nYour Score is: " + "number wrong: " + numWrong + " of: " + numProblems + " = " + Math.round(score) + "%\n");

      }
    }
    private static BasicMath[] subSet;
    private static BasicMath[] problemSet;

    static {
    }
};
