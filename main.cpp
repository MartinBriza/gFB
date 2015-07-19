#include "facebook-api.h"
#include <glib/gmain.h>

//#define USER "email"
//#define PASS "pass"
#include "SECRET.h"

#include <iostream>

fb_api_t *fb;

static void fb_cb_api_error(fb_api_t *api, GError *err, gpointer data) {
    std::cerr << __FUNCTION__ << ": " << err->message << std::endl;

}

static void fb_cb_api_auth(fb_api_t *api, gpointer data) {
    std::cerr << __FUNCTION__ << std::endl;
    fb_api_contacts(fb);
}

static void fb_cb_api_connect(fb_api_t *api, gpointer data) {
    std::cerr << __FUNCTION__ << std::endl;
    fb_api_message(fb, 0, false, ""); // TODO find out why it doesn't work when this stuff is not here
}

static void fb_cb_api_contacts(fb_api_t *api, GSList *users, gpointer data) {
    std::cerr << __FUNCTION__ << std::endl;
    fb_api_user_t *user;
    GSList        *l;
    gchar          uid[FB_ID_STRMAX];

    for (l = users; l != NULL; l = l->next) {
        user = (fb_api_user_t *) l->data;
        FB_ID_TO_STR(user->uid, uid);
        fprintf(stderr, "CONTACT! %s %s\n", user->name, uid);
    }
    fb_api_connect(fb);
}

static void fb_cb_api_message(fb_api_t *api, GSList *msgs, gpointer data) {
    std::cerr << __FUNCTION__ << std::endl;
    fb_api_msg_t     *msg;
    struct groupchat *gc;
    GSList           *l;
    gchar             uid[FB_ID_STRMAX];
    gchar             tid[FB_ID_STRMAX];

    for (l = msgs; l != NULL; l = l->next) {
        msg = (fb_api_msg_t *) l->data;
        FB_ID_TO_STR(msg->uid, uid);
        std::cerr << "MESSAGE! from: " << msg->uid << ": " << msg->text << std::endl;

        if (msg->tid == 0) {
            //imcb_buddy_msg(fata->ic, uid, (gchar*) msg->text, 0, 0);
            continue;
        }

        FB_ID_TO_STR(msg->tid, tid);

    }
}

static void fb_cb_api_presence(fb_api_t *api, GSList *press, gpointer data) {
    fb_api_pres_t *pres;
    GSList        *l;
    for (l = press; l != NULL; l = l->next) {
        pres  = (fb_api_pres_t *) l->data;
        std::cerr << pres->uid << " changed to " << (pres->active ? "active" : "inactive") << std::endl;
    }
}

static void fb_cb_api_thread_create(fb_api_t *api, fb_id_t tid, gpointer data) {
    std::cerr << __FUNCTION__ << std::endl;
}

static void fb_cb_api_thread_info(fb_api_t *api, fb_api_thread_t *thrd, gpointer data) {
    std::cerr << __FUNCTION__ << std::endl;
}

static void fb_cb_api_thread_list(fb_api_t *api, GSList *thrds, gpointer data) {
    std::cerr << __FUNCTION__ << std::endl;
}

static void fb_cb_api_typing(fb_api_t *api, fb_api_typing_t *typg, gpointer data) {
    std::cerr << __FUNCTION__ << std::endl;
}

static const fb_api_funcs_t funcs = {
    .error         = fb_cb_api_error,
    .auth          = fb_cb_api_auth,
    .connect       = fb_cb_api_connect,
    .contacts      = fb_cb_api_contacts,
    .message       = fb_cb_api_message,
    .presence      = fb_cb_api_presence,
    .thread_create = fb_cb_api_thread_create,
    .thread_info   = fb_cb_api_thread_info,
    .thread_list   = fb_cb_api_thread_list,
    .typing        = fb_cb_api_typing
};

static GMainLoop *loop = NULL;

int main(int argc, char *argv[]) {
    loop = g_main_new(false);
    fb = fb_api_new(&funcs, NULL);
    fb_api_rehash(fb);
    if (fb->token == NULL) {
        fb_api_auth(fb, USER, PASS);
    }
    else {
        fb_api_contacts(fb);
    }
    g_main_run(loop);
    return 0;
}
