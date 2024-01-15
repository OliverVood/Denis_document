<?php

	namespace Proj\Units\Consts;

	interface General {
		const ID						= ID_GENERAL;
		const NAME						= 'general';
		const TITLE						= 'Основное';

		const ACCESS_SETTING			= 1;
		const ACCESS_DB_CHECK			= 8;
		const ACCESS_DB_MAKE			= 9;
		const ACCESS_DB_STRUCTURE		= 10;

		const TEXT_ERROR_ACCESS			= 'Ошибка доступа. Недостаточно прав.';

	}