class Command
{
public:
    virtual void execute() = 0;
};

class JOIN_COMMAND : public Command
{
};