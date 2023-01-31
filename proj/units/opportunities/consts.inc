<?php

	namespace Proj\Units\Consts;

	interface Opportunities {
		const ID						= ID_OPPORTUNITIES;
		const NAME						= 'opportunities';

		const TABLES = [
			'opportunities' 			=> self::NAME,
			'opportunity'				=> 'opportunity'
		];

		const STATE_ERROR				= 0;
		const STATE_DRAFT				= 1;
		const STATE_ACTIVE				= 2;
		const STATE_INACTIVE			= 3;
		const STATE_DELETE				= 100;

		const STATES = [
			'error'						=> self::STATE_ERROR,
			'draft'						=> self::STATE_DRAFT,
			'active'					=> self::STATE_ACTIVE,
			'inactive'					=> self::STATE_INACTIVE,
			'delete'					=> self::STATE_DELETE
		];

		const PATH_COVER				= DIR_RESOURCE_IMAGE . "opportunities/";
		const PATH_COVER_RELATIVE		= '/proj/resource/image/opportunities/';
	}