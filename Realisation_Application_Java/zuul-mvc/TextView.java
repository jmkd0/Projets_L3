import java.util.Observable;
import java.util.Observer;


/**
 * TextView is a textual view of the Zuul game. It prints out texts to the 
 * screen.
 * 
 * @author Poul Henriksen
 * @version  1.0 (February 2005)
 */
public class TextView implements Observer
{
    private GameModel gameModel;

    public TextView(GameModel gameModel)
    {
        this.gameModel = gameModel;
    }

    public void printWelcome()
    {
        show("\n" + gameModel.getWelcomeString() + "\n");
        printLocationInfo();
    }
    
    private void printLocationInfo()
    {
        show(gameModel.getLocationInfo());
    }
    
    public void printGoodBye() 
    {
        show(gameModel.getGoodByeString());
    }
    
    public void printHelp()
    {
        show(gameModel.getHelpString());
    }
   
    public void show(String string) 
    {
        System.out.println(string);
    }
   
    public void update(Observable o, Object arg)
    {
        printLocationInfo();
    }
}
