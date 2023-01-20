<?php

	namespace Proj\Units\Consts;

	interface Users {
		const ID				= ID_USERS;
		const NAME				= 'users';

		const TABLES = [
			'users'				=> self::NAME,
		];
	}