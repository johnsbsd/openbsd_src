/*
 * Copyright (C) Internet Systems Consortium, Inc. ("ISC")
 *
 * Permission to use, copy, modify, and/or distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND ISC DISCLAIMS ALL WARRANTIES WITH
 * REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY
 * AND FITNESS.  IN NO EVENT SHALL ISC BE LIABLE FOR ANY SPECIAL, DIRECT,
 * INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
 * LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE
 * OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
 * PERFORMANCE OF THIS SOFTWARE.
 */

/* $Id: minfo_14.c,v 1.6 2020/02/24 17:43:52 florian Exp $ */

/* reviewed: Wed Mar 15 17:45:32 PST 2000 by brister */

#ifndef RDATA_GENERIC_MINFO_14_C
#define RDATA_GENERIC_MINFO_14_C

#define RRTYPE_MINFO_ATTRIBUTES (0)

static inline isc_result_t
totext_minfo(ARGS_TOTEXT) {
	isc_region_t region;
	dns_name_t rmail;
	dns_name_t email;
	dns_name_t prefix;
	isc_boolean_t sub;

	REQUIRE(rdata->type == dns_rdatatype_minfo);
	REQUIRE(rdata->length != 0);

	dns_name_init(&rmail, NULL);
	dns_name_init(&email, NULL);
	dns_name_init(&prefix, NULL);

	dns_rdata_toregion(rdata, &region);

	dns_name_fromregion(&rmail, &region);
	isc_region_consume(&region, rmail.length);

	dns_name_fromregion(&email, &region);
	isc_region_consume(&region, email.length);

	sub = name_prefix(&rmail, tctx->origin, &prefix);

	RETERR(dns_name_totext(&prefix, sub, target));

	RETERR(str_totext(" ", target));

	sub = name_prefix(&email, tctx->origin, &prefix);
	return (dns_name_totext(&prefix, sub, target));
}

static inline isc_result_t
fromwire_minfo(ARGS_FROMWIRE) {
	dns_name_t rmail;
	dns_name_t email;

	REQUIRE(type == dns_rdatatype_minfo);

	UNUSED(type);
	UNUSED(rdclass);

	dns_decompress_setmethods(dctx, DNS_COMPRESS_GLOBAL14);

	dns_name_init(&rmail, NULL);
	dns_name_init(&email, NULL);

	RETERR(dns_name_fromwire(&rmail, source, dctx, options, target));
	return (dns_name_fromwire(&email, source, dctx, options, target));
}

static inline isc_result_t
towire_minfo(ARGS_TOWIRE) {
	isc_region_t region;
	dns_name_t rmail;
	dns_name_t email;
	dns_offsets_t roffsets;
	dns_offsets_t eoffsets;

	REQUIRE(rdata->type == dns_rdatatype_minfo);
	REQUIRE(rdata->length != 0);

	dns_compress_setmethods(cctx, DNS_COMPRESS_GLOBAL14);

	dns_name_init(&rmail, roffsets);
	dns_name_init(&email, eoffsets);

	dns_rdata_toregion(rdata, &region);

	dns_name_fromregion(&rmail, &region);
	isc_region_consume(&region, name_length(&rmail));

	RETERR(dns_name_towire(&rmail, cctx, target));

	dns_name_fromregion(&rmail, &region);
	isc_region_consume(&region, rmail.length);

	return (dns_name_towire(&rmail, cctx, target));
}


static inline isc_result_t
fromstruct_minfo(ARGS_FROMSTRUCT) {
	dns_rdata_minfo_t *minfo = source;
	isc_region_t region;

	REQUIRE(type == dns_rdatatype_minfo);
	REQUIRE(source != NULL);
	REQUIRE(minfo->common.rdtype == type);
	REQUIRE(minfo->common.rdclass == rdclass);

	UNUSED(type);
	UNUSED(rdclass);

	dns_name_toregion(&minfo->rmailbox, &region);
	RETERR(isc_buffer_copyregion(target, &region));
	dns_name_toregion(&minfo->emailbox, &region);
	return (isc_buffer_copyregion(target, &region));
}

static inline isc_result_t
tostruct_minfo(ARGS_TOSTRUCT) {
	dns_rdata_minfo_t *minfo = target;
	isc_region_t region;
	dns_name_t name;
	isc_result_t result;

	REQUIRE(rdata->type == dns_rdatatype_minfo);
	REQUIRE(target != NULL);
	REQUIRE(rdata->length != 0);

	minfo->common.rdclass = rdata->rdclass;
	minfo->common.rdtype = rdata->type;
	ISC_LINK_INIT(&minfo->common, link);

	dns_name_init(&name, NULL);
	dns_rdata_toregion(rdata, &region);
	dns_name_fromregion(&name, &region);
	dns_name_init(&minfo->rmailbox, NULL);
	RETERR(name_duporclone(&name, &minfo->rmailbox));
	isc_region_consume(&region, name_length(&name));

	dns_name_fromregion(&name, &region);
	dns_name_init(&minfo->emailbox, NULL);
	result = name_duporclone(&name, &minfo->emailbox);
	if (result != ISC_R_SUCCESS)
		goto cleanup;
	return (ISC_R_SUCCESS);

 cleanup:
	dns_name_free(&minfo->rmailbox);
	return (ISC_R_NOMEMORY);
}




#endif	/* RDATA_GENERIC_MINFO_14_C */
