<?php

	namespace Proj\Units\Consts;

	interface Statistics {
		const ID				= ID_STATISTICS;
		const NAME				= 'statistics';

		const TABLES = [
			'ip'				=> self::NAME . '_ip',
			'act'				=> self::NAME . '_act'
		];
	}