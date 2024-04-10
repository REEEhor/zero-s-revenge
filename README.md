# Zero's revenge

You play as the number zero, that wants to take its revenge.
You stand against other numbers that will come at you in waves.
When you start the game, you will see a list of levels that you can play.

![image](https://github.com/REEEhor/zero-s-revenge/assets/141070564/6be20788-1158-4eaf-b3cd-0311ddf5e791)

Run using `$ make run`

# Controls
- **w a s d** - movement
- **space** - shoot
- **numbers** - selection of a gun (at the start of the level, only one gun can shoot. To be able to shoot with other guns, you have to pick up ammo bonus `==`, that drops from enemies - it will reload your currently selected gun)
- **p** - pause/unpause
- **q** - quit - while the game is paused, you can leave the level

Other bonuses:
- `<3` - **health bonus** - it will add back some lives you lost
- `2x` - **double bullets** - your bullets will deal double damage for a short period of time

# Configuration
- Define your own levels in `./examples/default/`.
- Here is the first level for example (see `/examples/default/beginner_level01.lvl`):
```
Structure of the level:
####################################### <- unbreakable wall
#                   W <- breakable wall
#                   W  B              #
#  B                W      BBBBB      #
#                                     #
#                                     #
#                          W          #
# P <- player initial position    S <- a place where enemies spawn
#             B            W          #
#                   W                 #
#                   W                 #
#   BBB             W               B <- a "box", easily breakable wall
#######################################

Definition of waves:
<WAVES>
1 1           - the first wave is one instance of the "1" enemy
1 2 | 4 1     - the second wave is one instance of the "2" enemy and four instances of the "1" enemy
1 5           - the third wave is one instance of the "5" enemy
5 3           - ...
1 9
```

- You can change the settings of the game in `/examples/default/default.cnfg` - the are restrains that check the validity of the variables you set.
- If you run the game using `./game path_to_config_file`, it will try to load its settings.

# Story
*It was a peaceful sunny day and numbers were playing outside. The game they played was adding and subtracting. Two numbers added themselves together and... Wow! New number! 3 and 5 created 8.*
>*Me! Me!*

*Shouted -3. I want to play as well. So the 3 and -3 added themselves and... What? The number they created was different. When it tried to add or subtract itself from any other number, nothing happened.*
> *We don't want to play with you!
Shouted someone.*


*Number 0, that was just born, was sad.*
> *Look! I bring you multiplication!*

*But when it tried to multiply itself with someone else, the other number disappeared.*

> *Ok, that is it!*

*said the big 63.*

> *Get out! Your multiplication is stupid, you don't belong here.The only thing you make is yourself, how selfish!*

*And so the 0 went away. But it asked itself...*
>*What if this is the thing that I want to do? I will multiply... no... even **DIVIDE!** every number, that said I was stupid.*

*So it picked up the gun that shoots multiplication a started shooting...*



