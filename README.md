##ROS simple package which covers:
- usage of publisher and subscriber
- usage of service and client

###For runing publisher and subscriber:
[*] don't forget to sourcer devel/setup.bash 
- At 1st terminal window run: roscore
- At 2nd terminal window run: rosrun vovka_pkg producer
- At 3rd terminal window run: rosrun vovka_pkg consumer

Python version:
- At 1st terminal window run: roscore
- At 2nd terminal window run: rosrun vovka_pkg producer.py
- At 3rd terminal window run: rosrun vovka_pkg consumer.py


You can mixed them or run all of them!

### Here you can also try service for finding max value
[*] don't forget to sourcer devel/setup.bash 
- At 1st terminal window run: roscore
- At 2nd terminal window run: rosrun vovka_pkg find_max_server
- At 3rd terminal window run: rosrun vovka_pkg find_max_client 3 -4 14 13 5
[*] except different amount of values > 1

Python version:
- At 1st terminal window run: roscore
- At 2nd terminal window run: rosrun vovka_pkg find_max_server.py
- At 3rd terminal window run: rosrun vovka_pkg find_max_client.py 3 -4 14 13 5
[*] except different amount of values > 1


### Run rviz
- [1] $ roslaunch simple_pkg fake_turtlebot.launch
- [2] $ rosrun rviz rviz -d `roscd simple_pkg`/sim.rviz
- [3] $ rosrun simple_pkg circle_movement.py

