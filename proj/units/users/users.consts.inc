<?php

	namespace Proj\Units\Consts;

	interface Users {
		const ID						= ID_USERS;
		const NAME						= 'users';
		const TITLE						= 'Пользователи';

		const TABLES = [
			'clients'					=> 'clients',
			'groups'					=> 'groups',
			'users'						=> self::NAME,
			'access_groups'				=> 'access_groups',
			'access_users'				=> 'access_users'
		];

		const STATE_GROUP_ERROR			= 0;
		const STATE_GROUP_ACTIVE		= 1;
		const STATE_GROUP_INACTIVE		= 2;
		const STATE_GROUP_DELETE		= 100;

		const STATES_GROUPS_VIEW = [
			self::STATE_GROUP_ERROR		=> 'Ошибка',
			self::STATE_GROUP_ACTIVE	=> 'Активная',
			self::STATE_GROUP_INACTIVE	=> 'Не активная',
			self::STATE_GROUP_DELETE	=> 'Удалена'
		];

		const STATE_USER_ERROR			= 0;
		const STATE_USER_ACTIVE			= 1;
		const STATE_USER_INACTIVE		= 2;
		const STATE_USER_BLOCK			= 3;
		const STATE_USER_DELETE			= 100;

		const STATES_USERS_VIEW = [
			self::STATE_USER_ERROR		=> 'Ошибка',
			self::STATE_USER_ACTIVE		=> 'Активный',
			self::STATE_USER_BLOCK		=> 'Не активный',
			self::STATE_USER_DELETE		=> 'Удалён'
		];

		const PERMISSION_UNDEFINED		= 'undefined';
		const PERMISSION_YES			= 'yes';
		const PERMISSION_NO				= 'no';

		const PERMISSIONS				= [
			self::PERMISSION_UNDEFINED,
			self::PERMISSION_YES,
			self::PERMISSION_NO
		];
	}