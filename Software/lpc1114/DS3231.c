unsigned char time_to_reg(unsigned char time)
{
    return (((time / 10) << 4) + (time % 10));
}

unsigned char reg_to_time(unsigned char reg)
{
    return (((reg >> 4) * 10) + (reg % 16));
}
