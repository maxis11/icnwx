////////////////////////////////////////////////////////////////////////////
// idea.h
//

#ifndef IDEA_H_9393IFMFJRE83838292092KDMDMNDNDJDND8383JDJMDKS9293NF
#define IDEA_H_9393IFMFJRE83838292092KDMDMNDNDJDND8383JDJMDKS9293NF

#include <stdint.h>
#ifdef __cplusplus
extern "C" {
#endif 

#ifdef _MSC_VER
typedef unsigned short u_int16_t;
typedef long int32_t;

#else
#include <sys/types.h>
#endif

	#define IDEA_KS_SIZE 104

	typedef uint16_t idea_cblock[4];
	typedef uint16_t idea_user_key[8];
	typedef uint16_t idea_ks[52];

	void idea_crypt(idea_cblock in, idea_cblock out, idea_ks key);
	void idea_invert_key(idea_ks key, idea_ks inv_key);
	void idea_expand_key(idea_user_key userKey, idea_ks key);

#ifdef __cplusplus
}
#endif 


#endif //IDEA_H_9393IFMFJRE83838292092KDMDMNDNDJDND8383JDJMDKS9293NF
