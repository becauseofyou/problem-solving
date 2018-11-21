#!/bin/bash  
for((i=1;i<=25;i++)); 
do   
    mv game$i.in input$i
    mv game$i.ans output$i
done  

