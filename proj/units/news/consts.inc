<?php

	namespace Proj\Units\Consts;

	interface News {
		const ID						= ID_NEWS;
		const NAME						= 'news';

		const TABLES = [
			'news'						=> self::NAME
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

		const PATH_COVER				= DIR_RESOURCE_IMAGE . 'news/';
		const PATH_COVER_RELATIVE		= '/proj/resource/image/news/';
	}