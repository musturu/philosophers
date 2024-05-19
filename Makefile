all :
	make -C philo/
	make -C philo_bonus/
	mv philo/philo ./phil
	mv philo_bonus/philo_bonus ./phil_bonus
	
clean :
	make -C philo/ clean
	make -C philo_bonus/ clean

fclean : 
	make -C philo_bonus/ fclean
	make -C philo/ fclean
	rm phil
	rm phil_bonus

re : fclean all
