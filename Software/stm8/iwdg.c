void init_iwdg(void)
{
  IWDG_KR  = 0x55;  // KEY_ACCESS
  // { 1.02sn wait setting
  IWDG_PR  = 0x06;  // prescaler max = 6 , min = 0 look at datasheet
  // IWDG_RLR = 0xFF;  // from 256 to 0 countdown , for instant reset write 0
  // }
  IWDG_RLR = 0x00;  // instant reset
  IWDG_KR  = 0x00;  // CLOSE ACCESS
  IWDG_KR  = 0xCC;  // KEY_ENABLE , start countdown
  // #define   refresh_iwdg ( IWDG_KR = 0xAA )
}
