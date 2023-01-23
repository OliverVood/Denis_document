<?php

	namespace Proj\Units\Consts;

	interface News {
		const ID				= ID_NEWS;
		const NAME				= 'news';

		const TABLES = [
			'news'				=> self::NAME
		];

		const STATES = [
			'error'				=> 0,
			'draft'				=> 1,
			'active'			=> 2,
			'inactive'			=> 3,
			'delete'			=> 100
		];
	}