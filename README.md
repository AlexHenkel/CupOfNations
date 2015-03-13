# CupOfNations

This is a soccer competition system (originally created to store Xbox FIFA tournaments for my friends) that starts from an
initial round and ends up with a winner. It also keeps a general record that is updated every time a competition is played.

This program uses a text file that stores the name of the player, games played, goals for, goals agains, and points. These
information allows the program to keep a general record every time the program is executed. The purpose of these standings are
that every tournament is played by different players, so this stores a quotient between points and games played, having as
tie-breaker the goals difference, goals for or goals against, following a normal League model.

The tournament that is played every time the program is executed has some options: having one group or two groups, and having
each pair of players play each other twice or once. If there are two games per pair, the away goles rule is applied.

During the group stage, the user can display at any time the groups standings, ordered by points or goals difference. Also the
program gives a random list of the matches for the user to follow, but that order is not mandatory. The last option is to store
a match, where you have to give the home and away player and the goals each one scored. After you complete all the matches, a
4th option appears to move to the next stage, which displays the final groups standings and the players that made it to the next
stage. If two players have the exact same standings, the winner is defined random.

These stage is conformed by 4 players, who play semifinals and the final game. In case that the semifinal ends in a tie (solved
in real life by penalty kicks) the user is required to write the name of the winner. These games of the final stage, do not
count to the general standigs stored in the file.
