#include <dpp/dpp.h>
#include "Utilities/console.hpp"
#include "Utilities/environment.hpp"
#include <cstdlib>
using namespace RichOut;
using namespace dpp;

int main() {
    EnvUtil::load_env();

    const char* token = std::getenv("DISCORD_BOT_TOKEN");
    if (!token) {
        rc::error("DISCORD_BOT_TOKEN environment variable not set.");
        rc::info("Did you make a .env file and declare a DISCORD_BOT_TOKEN variable?");
        return EXIT_FAILURE;
    }

    // Create THE bot
    dpp::cluster bot(token);
    bot.intents = dpp::i_default_intents | dpp::i_message_content;  // Add this line
    bot.on_log(dpp::utility::cout_logger());
    bot.on_slashcommand([](const dpp::slashcommand_t& event) {
        dpp::discord_client* shard = event.from->creator->get_shard(event.from->shard_id);
        double ws_latency = shard->websocket_ping * 1000;
        if (event.command.get_command_name() == "ping") {
            try
            {
                event.reply("Pong!\nLatency: " + std::to_string(ws_latency) + " ms");
                rc::success("Replied to /ping command.");
            }
            catch(const std::exception& e)
            {
                // std::cerr << e.what() << '\n';
                rc::error("Failed to reply to /ping command. Reason: " + std::string(e.what()));
            }
            
        }
    });

    bot.on_ready([&bot](const dpp::ready_t& event) {
        rc::success("Bot is ready. Registering slash commands...");

        dpp::slashcommand ping_cmd("ping", "Replies with Pong!", bot.me.id);
        bot.global_command_create(ping_cmd);

        rc::success("Slash commands registered.");
    });

    
    bot.start(dpp::st_wait);

    return 0;
}