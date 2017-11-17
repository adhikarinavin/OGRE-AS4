#include "UnitAI.h"
	UnitAI::UnitAI(Entity381* ent,Engine*eng):Aspect(ent)
	{
	    this->entity = ent;
	    this->engine=eng;
	}
	UnitAI::~UnitAI()
	{

	}
    void UnitAI::init()
    {
       if(!commands.empty())
       {
         commands.front()->init();
       }
    }
	void UnitAI::Tick(float dt)
	{
      if (!commands.empty())
        {
          commands.front()->tick(dt);
          if (commands.front()->done())
          {
            std::cout << "Unit AI Tick" << std::endl;
            commands.pop_front();
            if(!commands.empty())
            {
             commands.front()->init();
            }
          }
        }
	}
	void UnitAI::SetCommand(Command *c)
	{
	   //std::cout << "SetCommand Completed" << std::endl;
       commands.clear();
       commands.push_back(c);
	}
	void UnitAI::AddCommand(Command *c)
	{
        commands.push_back(c);
       // std::cout << "Add Command Completed" << std::endl;
	}

