#include <common.h>
#include <config.h>
#include <command.h>

#ifdef CONFIG_SYS_HUSH_PARSER
#include <hush.h>
#endif
int do_jack(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[]){
  
  if(argc == 1){
    int rcode = 0;

    #ifndef CONFIG_SYS_HUSH_PARSER
	    if (run_command("mmc part;\0", flag) < 0)
		    rcode = 1;
    #else
	    if (parse_string_outer("mmc part;\0",
			  FLAG_PARSE_SEMICOLON | FLAG_EXIT_FROM_LOOP) != 0)
		    rcode = 1;
    #endif
	  return rcode;
  }
  int rcode = 0;
  char buf[30];
  sprintf(buf, "setenv pnum %s\0", argv[1]);
  #ifndef CONFIG_SYS_HUSH_PARSER
	  if (run_command(buf, flag) < 0)
		  rcode = 1;
  #else
	  if (parse_string_outer(buf,
	    FLAG_PARSE_SEMICOLON | FLAG_EXIT_FROM_LOOP) != 0)
		  rcode = 1;
  #endif
  if(rcode)
	  return rcode;

  sprintf(buf, "setenv mmcroot \"/dev/mmcblk0p%c rw\"\0", argv[1][0]);

  #ifndef CONFIG_SYS_HUSH_PARSER
	  if (run_command(buf, flag) < 0)
		  rcode = 1;
  #else
	  if (parse_string_outer(buf,
	    FLAG_PARSE_SEMICOLON | FLAG_EXIT_FROM_LOOP) != 0)
		  rcode = 1;
  #endif
  if(rcode)
	  return rcode;



  rcode = 0;
  #ifndef CONFIG_SYS_HUSH_PARSER
	  if (run_command("setenv loaduimage ext2load mmc ${mmcdev}:${pnum} ${loadaddr} /boot/uImage\0", flag) < 0)
		  rcode = 1;
  #else
	  if (parse_string_outer("setenv loaduimage ext2load mmc ${mmcdev}:${pnum} ${loadaddr} /boot/uImage\0",
	    FLAG_PARSE_SEMICOLON | FLAG_EXIT_FROM_LOOP) != 0)
		  rcode = 1;
  #endif
  if(rcode)
	  return rcode;



  printf("booting~~~~\n");


  rcode = 0;
  #ifndef CONFIG_SYS_HUSH_PARSER
	  if (run_command("boot\0", flag) < 0)
		  rcode = 1;
  #else
	  if (parse_string_outer("boot\0",
	    FLAG_PARSE_SEMICOLON | FLAG_EXIT_FROM_LOOP) != 0)
		  rcode = 1;
  #endif
	return rcode;
}

U_BOOT_CMD(jack,10,1,do_jack,
        "Test program.\n", "Duh?\ns");

