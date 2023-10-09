# template-freeRTOS-project
Fork of the template project to support creating projects with freeRTOS with support for VScode


**Set Up:**

move the STLIB from your current location to /opt/ST-LIB:

To do so:

  go into the parent directory that contains the STLIB and move it to `/opt`
  
`sudo mv -r ST-LIB /opt`

We want to give permissions so that we can work without issues, also the build script moves some things around
better to give the user permissions

`sudo chmod a+rwx /opt/STLIB`

clone this repo:
`git clone git@github.com:HyperloopUPV-H8/template-freeRTOS-project.git`

open VS code 
and go into `Open workspace from file`
![open workspace](https://github.com/HyperloopUPV-H8/template-freeRTOS-project/assets/58850783/67d52a4c-d243-46ac-b272-4c93095e422e)

and select template-project.code-workspace
After selecting it a view similar to this one will open:


![image](https://github.com/HyperloopUPV-H8/template-freeRTOS-project/assets/58850783/acac1ec4-67d6-47e6-a53c-c0bfe2e1b480)

Further steps:

to build the program press `Ctrl` + `Shift` + `B`, and select the configuration you want to build

![image](https://github.com/HyperloopUPV-H8/template-freeRTOS-project/assets/58850783/4bd10955-94b2-48f2-b485-c84bdf5c6783)

If at the bottom you choose terminal view, you will see the output

![image](https://github.com/HyperloopUPV-H8/template-freeRTOS-project/assets/58850783/af8b6d27-a13d-44a1-9fc8-52fcdeebeaf7)

After the build has finished go into the menu on the left and select the Run and Debug view,

choose the configuration you want to run

![image](https://github.com/HyperloopUPV-H8/template-freeRTOS-project/assets/58850783/8fc8fe8a-3209-45c0-acf1-9f04f39ba1bb)

After launching, the following view shows:

![image](https://github.com/HyperloopUPV-H8/template-freeRTOS-project/assets/58850783/202e9a1a-139f-4dab-ab8a-ac8afe6037a6)

That's it you can start using VS Code for firmware development.





