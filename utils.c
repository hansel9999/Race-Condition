#include <stdio.h>
#include <math.h>

int get_cpu_perc(){
	static long time1=0, time2=0;
	static int flag=0;
	char line[128], dummy[32];
	FILE *p1 = popen("head -1 /proc/stat", "r");
	fgets(line,128, p1);
	sscanf(line, "%s %ld", dummy, &time2);
	fclose(p1);
	if(!flag){
		flag=1;
		time1=time2;
		return 0;
	}
	double cpu=time2-time1;
	cpu /= 16;
	time1=time2;
	return cpu;
}

int get_gpu_perc(){
    FILE *fp = popen("nvidia-smi --query-gpu=utilization.gpu --format=csv,noheader,nounits", "r");
    int gpu;
    fscanf(fp, "%d", &gpu);
    pclose(fp);
    return gpu;
}

int get_ram_perc(){
    FILE *fp = fopen("/proc/meminfo", "r");
    unsigned long long total, free, available;
    fscanf(fp, "MemTotal: %llu kB\nMemFree: %llu kB\nMemAvailable: %llu kB\n", &total, &free, &available);
    fclose(fp);
    unsigned long long used_memory = total - available;
    double ram_usage_percent = ((double)used_memory / (double)total) * 100.0;
    return ram_usage_percent;
}
