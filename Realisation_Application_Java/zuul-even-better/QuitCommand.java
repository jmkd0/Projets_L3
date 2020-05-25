/**
 * Implementation of the 'quit' user command.
 * 
 * @author Michael Kolling
 * @version 1.0 (December 2002)
 */
public class QuitCommand extends Command
{
    /**
     * Constructor for objects of class QuitCommand
     */
    public QuitCommand()
    {
    }

    /**
     * "Quit" was entered. Check the argument to see whether
     * we really quit the game. Return true, if we should quit, false
     * otherwise.
     */
    public boolean execute(Player player)
    {
        if(getSecondWord() == null) {
            return true;
        }
        else {
            System.out.println("I cannot quit that...");
            return false;
        }
    }

}
