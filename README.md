# En-Garde-
Fencing is supposed to be reaction speed based, but this game is a turn based fencing game? An interesting concept indeed...\

Objective:\
First one to get to 5 points wins

Rules:\
Input a number for the move you want to make, you can use a maximum of 6 actions per turn, any extra action spent this turn that exceeds 6 actions will take up spaces in the next turn\
If a player gets pushed off the piste, or leaves the piste on their own, the opponent will gain a point, and the starting position will shift forward favoring the opponent\
If two players attack and land hits at the same time, then whoever charged up an attack more will gain a point (fakes count as charging attacks)\
If both players have the same charge, both gain points\
Refer to moves and icons for more information

Pve:\
Play with a bot

Pvp:\
Play with a player, because there isn't a socket implementation yet, to play pvp, there must be a host, then stream on discord, while the 2 players dm the host the moves

Moves:
1. Lunge "--X>__"
2. Parry "BBB$"
3. Riposte "BB__X_"
4. Thrust "-X__"
5. Flèche "---X^___"
6. Fake "--"
7. Dodge "_<"
8. Move "_>"

Icons and their meanings:
- X means u hit, and only hits if adjacent 
- B means u block X
- \_  means wasting an action (do nothing)
- \- means charging an attack for X
- < means move back
- \> means move forwards, if its attached with an X, you move forwards and push them back by 1
- ^ = > * 3
- $ means knock them back by 1 if adjacent, and any dashes exists during the parry
