#pragma once

#include <iostream>

#include <json/json.h>

#include <libdevcore/Worker.h>
#include <libethcore/Farm.h>
#include <libethcore/Miner.h>

#include "PoolClient.h"
#include "getwork/EthGetworkClient.h"
#include "stratum/EthStratumClient.h"
#include "testing/SimulateClient.h"

using namespace std;

namespace dev
{
namespace eth
{
struct PoolSettings
{
    std::vector<std::shared_ptr<URI>> connections;  // List of connection definitions
    unsigned getWorkPollInterval = 10000;           // Interval (ms) between getwork requests
    unsigned noWorkTimeout = 14400;      // If no new jobs in this number of seconds drop connection
    unsigned poWEndTimeout = 180;        // If no new jobs in this number of seconds, set PoW end
    unsigned noResponseTimeout = 2;     // If no response in this number of seconds drop connection
    unsigned poolFailoverTimeout = 0;   // Return to primary pool after this number of minutes
    bool reportHashrate = true;         // Whether or not to report hashrate to pool
    unsigned hashRateInterval = 30;     // Interval in seconds among hashrate submissions
    std::string hashRateId =
        h256::random().hex(HexPrefix::Add);  // Unique identifier for HashRate submission
    unsigned connectionMaxRetries = 99;      // Max number of connection retries
    unsigned delayBeforeRetry = 10;          // Delay seconds before connect retry
    unsigned benchmarkBlock = 0;        // Block number used by SimulateClient to test performances
    std::string sysCallbackPoWStart = "";  // system command to call when PoW start
    std::string sysCallbackPoWEnd = "";    // system command to call when PoW end
    bool clearDAGPoWEnd = false;           // release GPU memory when PoW end
    bool callPoWEndAtStartup = false;      // call pow-end system command at startup
};

class PoolManager
{
public:
    PoolManager(PoolSettings _settings);
    static PoolManager& p() { return *m_this; }
    void addConnection(std::string _connstring);
    void addConnection(std::shared_ptr<URI> _uri);
    Json::Value getConnectionsJson();
    void setActiveConnection(unsigned int idx);
    void setActiveConnection(std::string& _connstring);
    std::shared_ptr<URI> getActiveConnection();
    void removeConnection(unsigned int idx);
    void start();
    void stop();
    bool isConnected() { return p_client->isConnected(); };
    bool isRunning() { return m_running; };
    int getCurrentEpoch();
    double getCurrentDifficulty();
    unsigned getConnectionSwitches();
    unsigned getEpochChanges();

private:
    void rotateConnect();

    void setClientHandlers();

    void showMiningAt();

    void setActiveConnectionCommon(unsigned int idx);

    void runSystemCommand(std::string command, bool async = true);

    boost::asio::io_context m_ios;

    PoolSettings m_Settings;

    void failovertimer_elapsed(const boost::system::error_code& ec);
    void submithrtimer_elapsed(const boost::system::error_code& ec);
    void reconnecttimer_elapsed(const boost::system::error_code& ec);

    std::atomic<bool> m_running = {false};
    std::atomic<bool> m_stopping = {false};
    std::atomic<bool> m_async_pending = {false};

    unsigned m_connectionAttempt = 0;

    std::string m_selectedHost = "";  // Holds host name (and endpoint) of selected connection
    std::atomic<unsigned> m_connectionSwitches = {0};

    unsigned m_activeConnectionIdx = 0;

    WorkPackage m_currentWp;

    boost::asio::io_service::strand m_io_strand;
    boost::asio::deadline_timer m_failovertimer;
    boost::asio::deadline_timer m_submithrtimer;
    boost::asio::deadline_timer m_reconnecttimer;

    std::unique_ptr<PoolClient> p_client = nullptr;

    std::atomic<unsigned> m_epochChanges = {0};

    static PoolManager* m_this;
};

}  // namespace eth
}  // namespace dev
