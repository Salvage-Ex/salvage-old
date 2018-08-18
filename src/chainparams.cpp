// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2014 The Bitcoin developers
// Copyright (c) 2014-2015 The Dash developers
// Copyright (c) 2015-2017 The PIVX developers
// Copyright (c) 2018 The Nitrous developers
// Copyright (c) 2018 The Salvage developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "chainparams.h"
#include "random.h"
#include "util.h"
#include "utilstrencodings.h"

#include <assert.h>
#include <boost/assign/list_of.hpp>

using namespace std;
using namespace boost::assign;

struct SeedSpec6 {
    uint8_t addr[16];
    uint16_t port;
};

#include "chainparamsseeds.h"

/**
 * Main network
 */

//! Convert the pnSeeds6 array into usable address objects.
static void convertSeed6(std::vector<CAddress>& vSeedsOut, const SeedSpec6* data, unsigned int count)
{
    // It'll only connect to one or two seed nodes because once it connects,
    // it'll get a pile of addresses with newer timestamps.
    // Seed nodes are given a random 'last seen time' of between one and two
    // weeks ago.
    const int64_t nOneWeek = 7 * 24 * 60 * 60;
    for (unsigned int i = 0; i < count; i++) {
        struct in6_addr ip;
        memcpy(&ip, data[i].addr, sizeof(ip));
        CAddress addr(CService(ip, data[i].port));
        addr.nTime = GetTime() - GetRand(nOneWeek) - nOneWeek;
        vSeedsOut.push_back(addr);
    }
}

//   What makes a good checkpoint block?
// + Is surrounded by blocks with reasonable timestamps
//   (no blocks before with a timestamp after, none after with
//    timestamp before)
// + Contains no strange transactions

static Checkpoints::MapCheckpoints mapCheckpoints =
    boost::assign::map_list_of
	(0, uint256("0x000001bd56d3caf0a808f56cd992ad820d07810ff0daa589a561470393a3979c"));
;
static const Checkpoints::CCheckpointData data = {
    &mapCheckpoints,
    1534561070, // * UNIX timestamp of last checkpoint block
    0,          // * total number of transactions between genesis and last checkpoint (the tx=... number in the SetBestChain debug.log lines)
    720         // * estimated number of transactions per day after checkpoint
};

static Checkpoints::MapCheckpoints mapCheckpointsTestnet =
    boost::assign::map_list_of
 	(0, uint256("0x0000026bbe805b61a2dab88a79f32e589e7dc3de6ee053ed1dbafe0a4568ff26"));
;

static const Checkpoints::CCheckpointData dataTestnet = {
    &mapCheckpointsTestnet,
    1534560210, // * UNIX timestamp of last checkpoint block
    0,          // * total number of transactions between genesis and last checkpoint (the tx=... number in the SetBestChain debug.log lines)
    720         // * estimated number of transactions per day after checkpoint
};

static Checkpoints::MapCheckpoints mapCheckpointsRegtest =
    boost::assign::map_list_of(0, uint256("0x"));
	
static const Checkpoints::CCheckpointData dataRegtest = {
    &mapCheckpointsRegtest,
    0,
    0,
    0};

class CMainParams : public CChainParams
{
public:
    CMainParams()
    {
        networkID                      = CBaseChainParams::MAIN;
        strNetworkID                   = "main";

        /**
         * The message start string is designed to be unlikely to occur in normal data.
         * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
         * a large 4-byte int at any alignment.
         */
        pchMessageStart[0]             = 0x62;
        pchMessageStart[1]             = 0x4A;
        pchMessageStart[2]             = 0x57;
        pchMessageStart[3]             = 0x44;
        vAlertPubKey                   = ParseHex("042b57e084c4cbbb9a8a4795e1c0e2c895a8e31ca9c4e2c6deba83b53d4f729ee5d96c8513b2f5214b022e9a23606374af5f259477928ec44a51f53de67193730b");
        nDefaultPort                   = 16999;
        bnProofOfWorkLimit             = ~uint256(0) >> 20;
        nSubsidyHalvingInterval        = 999999;
        nMaxReorganizationDepth        = 100;
        nEnforceBlockUpgradeMajority   = 510;
        nRejectBlockOutdatedMajority   = 650;
        nToCheckBlockUpgradeMajority   = 1000;
        nMinerThreads                  = 0;
        nTargetTimespan                = 10 * 60; // 10 minutes
        nTargetSpacing                 = 2 * 60; // 2 minute block time
        nLastPOWBlock                  = 1000;
        nMaturity                      = 40;
        nMasternodeCountDrift          = 20;
        nModifierUpdateBlock           = 50000; // we use the version 2 for dmd ** not used **
        nMaxMoneyOut                   = 250000000 * COIN;

	    //* variable masternode collateral
        nMinCollateral                 = 1250;

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 63);		// Start with 'S' from https://en.bitcoin.it/wiki/List_of_address_prefixes
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 65);		// Start with 'T' from https://en.bitcoin.it/wiki/List_of_address_prefixes
        base58Prefixes[SECRET_KEY]     = std::vector<unsigned char>(1, 193);
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x3F)(0x46)(0x25)(0x37).convert_to_container<std::vector<unsigned char> >(); // Start with 'SVGP'
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x3F)(0x46)(0x25)(0x3F).convert_to_container<std::vector<unsigned char> >(); // Start with 'SVGS'
        base58Prefixes[EXT_COIN_TYPE]  = boost::assign::list_of(0x80)(0x00)(0x92)(0xf0).convert_to_container<std::vector<unsigned char> >(); // BIP44 coin type is from https://github.com/satoshilabs/slips/blob/master/slip-0044.md 109 	0x8000006d

        const char* pszTimestamp       = "Salvage Team 18 Aug 2018 we rules the world";
        CMutableTransaction txNew;
        txNew.vin.resize(1);
        txNew.vout.resize(1);
        txNew.vin[0].scriptSig         = CScript() << 486604799 << CScriptNum(4) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        txNew.vout[0].nValue           = 10 * COIN;
        txNew.vout[0].scriptPubKey     = CScript() << ParseHex("0483e3f08209f63c7634ed8f73edba2faa66abf6123578922c0a5f280f8348e4d16545e800ff3e2337ba90006112759f6c2b128e4c3a7bdd041fd925c12f4c3fa7") << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock          = 0;
        genesis.hashMerkleRoot         = genesis.BuildMerkleTree();
        genesis.nVersion               = 1;
        genesis.nTime                  = 1534561070;
        genesis.nBits                  = 184759812;
        genesis.nNonce                 = 567550;
		
        hashGenesisBlock               = genesis.GetHash();
        //printf("Main Hash   %s\n", hashGenesisBlock.ToString().c_str());
        //printf("Main Merkle %s\n", genesis.hashMerkleRoot.ToString().c_str());
		
		assert(hashGenesisBlock        == uint256("0x000001bd56d3caf0a808f56cd992ad820d07810ff0daa589a561470393a3979c"));
		assert(genesis.hashMerkleRoot  == uint256("83975702c3d22cd91ba5350f2b22f32dbc4fb6422c630d9061fbb9b17e3965a0"));
        
        //vFixedSeeds.clear();
        //vSeeds.clear();
        vSeeds.push_back(CDNSSeedData("seed01.salvageproject.org", "seed01.salvageproject.org"));
        vSeeds.push_back(CDNSSeedData("seed02.salvageproject.org", "seed02.salvageproject.org"));
        vSeeds.push_back(CDNSSeedData("seed03.salvageproject.org", "seed03.salvageproject.org"));
        vSeeds.push_back(CDNSSeedData("seed04.salvageproject.org", "seed04.salvageproject.org"));
        vSeeds.push_back(CDNSSeedData("seed05.salvageproject.org", "seed05.salvageproject.org"));

        convertSeed6(vFixedSeeds, pnSeed6_main, ARRAYLEN(pnSeed6_main));

        fRequireRPCPassword            = true;
        fMiningRequiresPeers           = false /*true*/;
        fAllowMinDifficultyBlocks      = false;
        fDefaultConsistencyChecks      = false;
        fRequireStandard               = true;
        fMineBlocksOnDemand            = false;
        fSkipProofOfWorkCheck          = false;
        fTestnetToBeDeprecatedFieldRPC = false;
        fHeadersFirstSyncingActive     = false;

        nPoolMaxTransactions           = 3;
        strSporkKey                    = "04edc2fb6af45031b3e90ab75758db463181841ed14e190de37a2d13d6b8377cc09bb37a35f6080ef6b7dfd93c288ad44b90e4af06c5ac95c67405204ace41f1eb";
        strDarksendPoolDummyAddress    = "NQM4tzZum4iLeK9gGHdPYW96ewcE6wFAyh";
        nStartMasternodePayments       = 1534550400; 	// Saturday, 18 August 2018 00:00:00  ** NOT USED **
    }

    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return data;
    }
};
static CMainParams mainParams;

/**
 * Testnet (v3)
 */
class CTestNetParams : public CMainParams
{
public:
    CTestNetParams()
    {
        networkID                      = CBaseChainParams::TESTNET;
        strNetworkID                   = "test";
        pchMessageStart[0]             = 0x24;
        pchMessageStart[1]             = 0x61;
        pchMessageStart[2]             = 0x5A;
        pchMessageStart[3]             = 0x66;
        vAlertPubKey                   = ParseHex("04f56fa33b1d12a2323b85eaac7aadb2e2f0f8870202a41c5e94cab5e12fa0c3f20dd5ced3ab432ddc7c9a8082fda49d0f93a91dee1d98ccb3cbe94163a7876e97");
        nDefaultPort                   = 17999;
        nEnforceBlockUpgradeMajority   = 51;
        nRejectBlockOutdatedMajority   = 75;
        nToCheckBlockUpgradeMajority   = 100;
        nMinerThreads                  = 0;
        nTargetTimespan                = 10 * 60;
        nTargetSpacing                 = 2 * 60; // 2 minute block time
        nLastPOWBlock                  = 200;
        nMaturity                      = 15;
        nModifierUpdateBlock           = 51197; //approx Mon, 30 Apr 2018 04:00:00 GMT
        nMaxMoneyOut                   = 250000000 * COIN;

        //! Modify the testnet genesis block so the timestamp is valid for a later start.
        genesis.nTime                  = 1534561191;
        genesis.nNonce                 = 643237;

        hashGenesisBlock               = genesis.GetHash();
        //printf("Test Hash   %s\n", hashGenesisBlock.ToString().c_str());

        assert(hashGenesisBlock        == uint256("0x00000e48d468bc672b846f4051131a73f33ab07f010bbc743e5b17999e863c79"));

        //vFixedSeeds.clear();
        //vSeeds.clear();
        vSeeds.push_back(CDNSSeedData("seed01.salvageproject.org", "seed01.salvageproject.org"));
        vSeeds.push_back(CDNSSeedData("seed02.salvageproject.org", "seed02.salvageproject.org"));
        vSeeds.push_back(CDNSSeedData("seed03.salvageproject.org", "seed03.salvageproject.org"));
        vSeeds.push_back(CDNSSeedData("seed04.salvageproject.org", "seed04.salvageproject.org"));
        vSeeds.push_back(CDNSSeedData("seed05.salvageproject.org", "seed05.salvageproject.org"));

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 125);	// Start with 's' from https://en.bitcoin.it/wiki/List_of_address_prefixes
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 127);	// start with 't' from https://en.bitcoin.it/wiki/List_of_address_prefixes
        base58Prefixes[SECRET_KEY]     = std::vector<unsigned char>(1, 193);
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x3F)(0x46)(0x25)(0x41).convert_to_container<std::vector<unsigned char> >(); // Start with 'SVGT'
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x3F)(0x46)(0x25)(0x44).convert_to_container<std::vector<unsigned char> >(); // Start with 'SVGU'
        base58Prefixes[EXT_COIN_TYPE]  = boost::assign::list_of(0x80)(0x00)(0x00)(0x01).convert_to_container<std::vector<unsigned char> >(); // Testnet Salvage BIP44 coin type is '1' (All coin's testnet default)

        convertSeed6(vFixedSeeds, pnSeed6_test, ARRAYLEN(pnSeed6_test));

        fRequireRPCPassword            = true;
        fMiningRequiresPeers           = false /*true*/;
        fAllowMinDifficultyBlocks      = true;
        fDefaultConsistencyChecks      = false;
        fRequireStandard               = false;
        fMineBlocksOnDemand            = false;
        fTestnetToBeDeprecatedFieldRPC = true;

        nPoolMaxTransactions           = 2;
        strSporkKey                    = "049e62470887f7060a8722853bf55aad08c1e891a4cc2d06f874b9ce0559af377d8c2431a5706b7cea887b74bf4d573d120f95c74ea874813cb84fcf1020fa6257";
        strDarksendPoolDummyAddress    = "";
        nStartMasternodePayments       = 1534550400; 	// Saturday, 18 August 2018 00:00:00
    }
    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return dataTestnet;
    }
};
static CTestNetParams testNetParams;

/**
 * Regression test
 */
class CRegTestParams : public CTestNetParams
{
public:
    CRegTestParams()
    {
        networkID = CBaseChainParams::REGTEST;
        strNetworkID = "regtest";
        pchMessageStart[0] = 0x6A;
        pchMessageStart[1] = 0x34;
        pchMessageStart[2] = 0x51;
        pchMessageStart[3] = 0x54;
        nSubsidyHalvingInterval = 150;
        nEnforceBlockUpgradeMajority = 750;
        nRejectBlockOutdatedMajority = 950;
        nToCheckBlockUpgradeMajority = 1000;
        nMinerThreads = 1;
        nTargetTimespan = 24 * 60 * 60;
        nTargetSpacing = 2 * 60; // 2 minute block time
        bnProofOfWorkLimit = ~uint256(0) >> 1;
        nDefaultPort = 17555;
        genesis.nTime = 1528140682;
        genesis.nBits = 0x207fffff;
        genesis.nNonce = 987655;
		
        hashGenesisBlock = genesis.GetHash();

        //printf("Reg Hash   %s\n", hashGenesisBlock.ToString().c_str());
        //assert(hashGenesisBlock == uint256("0x45bc75e6f085ce607ac39fe76d261b2e3d7ef19fe701e5061c5e7850c8b00533"));

        //vFixedSeeds.clear();
        //vSeeds.clear();
        //vSeeds.push_back(CDNSSeedData("seed01.salvage.org", "seed01.salvage.org"));
        //vSeeds.push_back(CDNSSeedData("seed02.salvage.org", "seed02.salvage.org"));
        //vSeeds.push_back(CDNSSeedData("seed03.salvage.org", "seed03.salvage.org"));
        //vSeeds.push_back(CDNSSeedData("seed04.salvage.org", "seed04.salvage.org"));
        //vSeeds.push_back(CDNSSeedData("seed05.salvage.org", "seed05.salvage.org"));

        fRequireRPCPassword = false;
        fMiningRequiresPeers = false;
        fAllowMinDifficultyBlocks = true;
        fDefaultConsistencyChecks = true;
        fRequireStandard = false;
        fMineBlocksOnDemand = true;
        fTestnetToBeDeprecatedFieldRPC = false;
    }
    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return dataRegtest;
    }
};
static CRegTestParams regTestParams;

/**
 * Unit test
 */
class CUnitTestParams : public CMainParams, public CModifiableParams
{
public:
    CUnitTestParams()
    {
        networkID = CBaseChainParams::UNITTEST;
        strNetworkID = "unittest";
        nDefaultPort = 42323;
        vFixedSeeds.clear(); //! Unit test mode doesn't have any fixed seeds.
        vSeeds.clear();      //! Unit test mode doesn't have any DNS seeds.

        fRequireRPCPassword = false;
        fMiningRequiresPeers = false;
        fDefaultConsistencyChecks = true;
        fAllowMinDifficultyBlocks = false;
        fMineBlocksOnDemand = true;
    }

    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        // UnitTest share the same checkpoints as MAIN
        return data;
    }

    //! Published setters to allow changing values in unit test cases
    virtual void setSubsidyHalvingInterval(int anSubsidyHalvingInterval) { nSubsidyHalvingInterval = anSubsidyHalvingInterval; }
    virtual void setEnforceBlockUpgradeMajority(int anEnforceBlockUpgradeMajority) { nEnforceBlockUpgradeMajority = anEnforceBlockUpgradeMajority; }
    virtual void setRejectBlockOutdatedMajority(int anRejectBlockOutdatedMajority) { nRejectBlockOutdatedMajority = anRejectBlockOutdatedMajority; }
    virtual void setToCheckBlockUpgradeMajority(int anToCheckBlockUpgradeMajority) { nToCheckBlockUpgradeMajority = anToCheckBlockUpgradeMajority; }
    virtual void setDefaultConsistencyChecks(bool afDefaultConsistencyChecks) { fDefaultConsistencyChecks = afDefaultConsistencyChecks; }
    virtual void setAllowMinDifficultyBlocks(bool afAllowMinDifficultyBlocks) { fAllowMinDifficultyBlocks = afAllowMinDifficultyBlocks; }
    virtual void setSkipProofOfWorkCheck(bool afSkipProofOfWorkCheck) { fSkipProofOfWorkCheck = afSkipProofOfWorkCheck; }
};

static CUnitTestParams unitTestParams;

static CChainParams* pCurrentParams = 0;

CModifiableParams* ModifiableParams()
{
    assert(pCurrentParams);
    assert(pCurrentParams == &unitTestParams);
    return (CModifiableParams*)&unitTestParams;
}

const CChainParams& Params()
{
    assert(pCurrentParams);
    return *pCurrentParams;
}

CChainParams& Params(CBaseChainParams::Network network)
{
    switch (network) {
    case CBaseChainParams::MAIN:
        return mainParams;
    case CBaseChainParams::TESTNET:
        return testNetParams;
    case CBaseChainParams::REGTEST:
        return regTestParams;
    case CBaseChainParams::UNITTEST:
        return unitTestParams;
    default:
        assert(false && "Unimplemented network");
        return mainParams;
    }
}

void SelectParams(CBaseChainParams::Network network)
{
    SelectBaseParams(network);
    pCurrentParams = &Params(network);
}

bool SelectParamsFromCommandLine()
{
    CBaseChainParams::Network network = NetworkIdFromCommandLine();
    if (network == CBaseChainParams::MAX_NETWORK_TYPES)
        return false;

    SelectParams(network);
    return true;
}
