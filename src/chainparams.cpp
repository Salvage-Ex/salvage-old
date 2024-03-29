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
	(0, uint256("0000049e70db758199bca1a530c68ea0162558b42abba1f60a60d0991ff60314"));
;
static const Checkpoints::CCheckpointData data = {
    &mapCheckpoints,
    1535069268, // * UNIX timestamp of last checkpoint block
    0,          // * total number of transactions between genesis and last checkpoint (the tx=... number in the SetBestChain debug.log lines)
    720         // * estimated number of transactions per day after checkpoint
};

static Checkpoints::MapCheckpoints mapCheckpointsTestnet =
    boost::assign::map_list_of
 	(0, uint256("00000f52e502b6125d83ebd7fb8c8914e1b25f7801e65afbc8a5c6b3e252435d"));
;

static const Checkpoints::CCheckpointData dataTestnet = {
    &mapCheckpointsTestnet,
    1535069405, // * UNIX timestamp of last checkpoint block
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
        vAlertPubKey                   = ParseHex("04801fc7f9fb1dea0660fd5448a7e16feca056e762d2da6f64a0b7262a04ac76a5dedef072ae9daada2f2d3080bfcb3861b91b73ad6ceaf2c0ab1f87416f19252d");
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

        const char* pszTimestamp       = "Some trash is recycled, some is thrown away, some ends up where it shouldn't end up.";
        CMutableTransaction txNew;
        txNew.vin.resize(1);
        txNew.vout.resize(1);
        txNew.vin[0].scriptSig         = CScript() << 486604799 << CScriptNum(4) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        txNew.vout[0].nValue           = 0 * COIN;
        txNew.vout[0].scriptPubKey     = CScript() << ParseHex("0483e3f08209f63c7634ed8f73edba2faa66abf6123578922c0a5f280f8348e4d16545e800ff3e2337ba90006112759f6c2b128e4c3a7bdd041fd925c12f4c3fa7") << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock          = 0;
        genesis.hashMerkleRoot         = genesis.BuildMerkleTree();
        genesis.nVersion               = 1;
        genesis.nTime                  = 1535069268;
        genesis.nBits                  = 504365055;
        genesis.nNonce                 = 3271076;
		
        hashGenesisBlock               = genesis.GetHash();
        // printf("Main Hash   %s\n", hashGenesisBlock.ToString().c_str());
        //printf("Main Merkle %s\n", genesis.hashMerkleRoot.ToString().c_str());
		
		assert(hashGenesisBlock        == uint256("0000049e70db758199bca1a530c68ea0162558b42abba1f60a60d0991ff60314"));
		assert(genesis.hashMerkleRoot  == uint256("827768506cc21bf011726794ec9a605829591df56847317bf7a3e458328ffc00"));
        
        //vFixedSeeds.clear();
        //vSeeds.clear();
        vSeeds.push_back(CDNSSeedData("seed01.salvageproject.org", "seed01.salvageproject.org"));
        vSeeds.push_back(CDNSSeedData("seed02.salvageproject.org", "seed02.salvageproject.org"));
        vSeeds.push_back(CDNSSeedData("seed03.salvageproject.org", "seed03.salvageproject.org"));
        vSeeds.push_back(CDNSSeedData("seed04.salvageproject.org", "seed04.salvageproject.org"));
        vSeeds.push_back(CDNSSeedData("seed05.salvageproject.org", "seed05.salvageproject.org"));
        vSeeds.push_back(CDNSSeedData("seed06.salvageproject.org", "seed06.salvageproject.org"));
        vSeeds.push_back(CDNSSeedData("seed07.salvageproject.org", "seed07.salvageproject.org"));
        vSeeds.push_back(CDNSSeedData("seed08.salvageproject.org", "seed08.salvageproject.org"));
        vSeeds.push_back(CDNSSeedData("seed09.salvageproject.org", "seed09.salvageproject.org"));



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
        strSporkKey                    = "04323d68746d48c4360caa85b40fb8536c729d03c9c3dd8258dda0f5945a0eeaed8ec2bbdb8a8ddb84502763c0cf8c6bfb1838faa660a5d0ea066711d6038e0e2c";
        strDarksendPoolDummyAddress    = "sejss9knA6c3EATnuraxmZvWBfUYkw2cqW";
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
        vAlertPubKey                   = ParseHex("0464036395ef1dceec79404ca837b7ca46a586b6f676fbcd200ee61d3111a0d3a041181ee516ce402087daec9ff22bcf197420c9de1db500cbd18598bd2b40fb52");
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
        genesis.nTime                  = 1535069405;
        genesis.nNonce                 = 173831;

        hashGenesisBlock               = genesis.GetHash();
        //printf("Test Hash   %s\n", hashGenesisBlock.ToString().c_str());

        assert(hashGenesisBlock        == uint256("00000f52e502b6125d83ebd7fb8c8914e1b25f7801e65afbc8a5c6b3e252435d"));

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
        strSporkKey                    = "047b28193ff31a5234504edfe29f5cf9cd3bc99e916a7bc694b954b7c997a8eca6254cc1a560174bcb23e0461aa552cc47437087d7ebab552ec9679a7823983fc9";
        strDarksendPoolDummyAddress    = "sMPC3oo2a3L8z63LAmPJtqmX4SwJ3tMt5a";
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
